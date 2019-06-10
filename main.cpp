#include <QCoreApplication>
#include <QDebug>
#include <QFuture>
#include <QtConcurrent>
#include <QDirIterator>

void count(QString path)
{
    //https://doc.qt.io/qt-5/qdiriterator.html
    QDirIterator it(path,QDir::Files,QDirIterator::Subdirectories);
    int value = 0;
    while (it.hasNext())
    {
        qInfo() << it.next();
        value++;
    }

    qInfo() << "Found " << value << " files";
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QDir root = QDir::current();
    root.cdUp();

    QFuture<void> future = QtConcurrent::run(&count, root.path());

    qInfo() << "Counting files...";

    //Do something else while we wait

    future.waitForFinished();

    qInfo() << "Done";

    return a.exec();
}
