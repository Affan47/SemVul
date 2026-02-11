AVCFileExists(const char *pszPath, const char *pszName)
{
    char        *pszBuf;
    GBool       bFileExists = FALSE;
    FILE        *fp;

    pszBuf = (char*)CPLMalloc((strlen(pszPath)+strlen(pszName)+1)*
                              sizeof(char));
    sprintf(pszBuf, "%s%s", pszPath, pszName);

    AVCAdjustCaseSensitiveFilename(pszBuf);

    if ((fp = VSIFOpen(pszBuf, "rb")) != NULL)
    {
        bFileExists = TRUE;
        VSIFClose(fp);
    }

    CPLFree(pszBuf);

    return bFileExists;
}
