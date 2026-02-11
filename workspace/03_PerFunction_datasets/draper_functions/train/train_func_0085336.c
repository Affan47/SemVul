pos()const
{
    if(p->zip == NULL)
    {
        qWarning("QuaZipFile::pos(): call setZipName() or setZip() first");
        return -1;
    }
    if(!isOpen())
    {
        qWarning("QuaZipFile::pos(): file is not open");
        return -1;
    }
    if(openMode()&ReadOnly)


    {
        return unztell(p->zip->getUnzFile()) - QIODevice::bytesAvailable();
    }
    else
    {
        return p->writePos;
    }
}
