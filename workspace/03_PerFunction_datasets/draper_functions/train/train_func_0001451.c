_AVCE00ReadScanE00(AVCE00ReadE00Ptr psRead)
{
    AVCE00ParseInfo *psInfo = psRead->hParseInfo;

    const char *pszLine;
    const char *pszName = 0;
    void       *obj;
    int        iSect = 0;

    while (CPLGetLastErrorNo() == 0 &&
            (pszLine = CPLReadLine(psRead->hFile) ) != NULL )
    {
        obj = _AVCE00ReadNextLineE00(psRead, pszLine);

        if (obj)
        {
            pszName = 0;
            switch (psInfo->eFileType)
            {
            case AVCFileARC:
                pszName = "ARC";
                break;

            case AVCFilePAL:
                pszName = "PAL";
                break;

            case AVCFileCNT:
                pszName = "CNT";
                break;

            case AVCFileLAB:
                pszName = "LAB";
                break;

            case AVCFileRPL:
                pszName = "RPL";
                break;

            case AVCFileTXT:
                pszName = "TXT";
                break;

            case AVCFileTX6:
                pszName = "TX6";
                break;

            case AVCFilePRJ:
                pszName = "PRJ";
                break;

            case AVCFileTABLE:
                pszName = psInfo->hdr.psTableDef->szTableName;
                break;

            default:
                break;
            }

            if (pszName && (psRead->numSections == 0 ||
                    psRead->pasSections[iSect].eType != psInfo->eFileType ||
                    !EQUAL(pszName, psRead->pasSections[iSect].pszName)))
            {
                iSect = _AVCIncreaseSectionsArray(&(psRead->pasSections),
                                      &(psRead->numSections), 1);

                psRead->pasSections[iSect].eType = psInfo->eFileType;

                psRead->pasSections[iSect].pszName = CPLStrdup(pszName);
                psRead->pasSections[iSect].pszFilename = CPLStrdup(psRead->pszCoverPath);
                psRead->pasSections[iSect].nLineNum = psInfo->nStartLineNum;
                psRead->pasSections[iSect].nFeatureCount = 0;
            }

            if (pszName && psRead->numSections)
            {

                ++psRead->pasSections[iSect].nFeatureCount;
            }
        }
    }
}
