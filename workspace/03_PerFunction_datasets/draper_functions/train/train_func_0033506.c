setZipName(const QString& zipName)
{
    if(isOpen())
    {
        qWarning("QuaZipFile::setZipName(): file is already open - can not set ZIP name");
        return;
    }
    if(p->zip != NULL && p->internal)
    {
        delete p->zip;
    }
    p->zip = new QuaZip(zipName);
    p->internal = true;
}
