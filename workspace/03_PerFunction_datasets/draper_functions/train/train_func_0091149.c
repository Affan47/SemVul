getActualFileName()const
{
    p->setZipError(UNZ_OK);
    if(p->zip == NULL || (openMode() & WriteOnly))
    {
        return QString();
    }
    QString name = p->zip->getCurrentFileName();
    if(name.isNull())
    {
        p->setZipError(p->zip->getZipError());
    }
    return name;
}
