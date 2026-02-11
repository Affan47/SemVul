isValid()
{


    char buffer[13];

    char* szHeader;
    short version;


    size_t nRead = VSIFReadL( buffer, 1, sizeof(buffer)-1, pGTMFile );
    if (nRead <= 0)
    {
        VSIFCloseL( pGTMFile );
        pGTMFile = NULL;
        return FALSE;
    }
    buffer[12] = '\0';


    if (buffer[0] == 0x1f && ((unsigned char*)buffer)[1] == 0x8b &&
        strncmp(pszFilename, "/vsigzip/", strlen("/vsigzip/")) != 0)
    {
        char* pszGZIPFileName = (char*)CPLMalloc(
                           strlen("/vsigzip/") + strlen(pszFilename) + 1);
        sprintf(pszGZIPFileName, "/vsigzip/%s", pszFilename);
        VSILFILE* fp = VSIFOpenL(pszGZIPFileName, "rb");
        if (fp)
        {
            VSILFILE* pGTMFileOri = pGTMFile;
            pGTMFile = fp;
            if (isValid())
            {
                VSIFCloseL(pGTMFileOri);
                CPLFree(pszGZIPFileName);
                return TRUE;
            }
            else
            {
                if (pGTMFile)
                    VSIFCloseL(pGTMFile);
                pGTMFile = pGTMFileOri;
            }
        }
        CPLFree(pszGZIPFileName);
    }

    version = CPL_LSBINT16PTR(buffer);

    szHeader = buffer + 2;
    if (version == 211 && strcmp(szHeader, "TrackMaker") == 0 )
    {
        return TRUE;
    }
    return FALSE;
}
