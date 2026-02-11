AVCE00ReadNextObjectE00(AVCE00ReadE00Ptr psRead)
{
    const char *pszLine;
    void       *obj = NULL;

    do
    {
        pszLine = CPLReadLine(psRead->hFile);
        if (pszLine == 0)
            break;
        obj = _AVCE00ReadNextLineE00(psRead, pszLine);
    }
    while (obj == NULL &&
            (psRead->bReadAllSections ||
             psRead->eCurFileType != AVCFileUnknown) &&
            CPLGetLastErrorNo() == 0);
    return obj;
}
