extractFile(QString fileCompressed, QString fileName, QString fileDest)
{

    QuaZip zip(fileCompressed);
    if(!zip.open(QuaZip::mdUnzip))
    {
        return QString();
    }


    if(fileDest.isEmpty())
    {
        fileDest = fileName;
    }
    if(!extractFile(&zip, fileName, fileDest))
    {
        return QString();
    }


    zip.close();
    if(zip.getZipError() != 0)
    {
        removeFile(QStringList(fileDest));
        return QString();
    }
    return QFileInfo(fileDest).absoluteFilePath();
}
