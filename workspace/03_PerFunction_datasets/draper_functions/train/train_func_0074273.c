AVCE00ParseNextTableRecLine(AVCE00ParseInfo *psInfo,
                                        const char *pszLine)
{
    AVCField    *pasFields = NULL;
    AVCTableDef *psTableDef;
    int         i;

    CPLAssert(psInfo->eFileType == AVCFileTABLE);

    psTableDef = psInfo->hdr.psTableDef;

    if (psInfo->bForceEndOfSection || psTableDef->numFields == 0 ||
        psTableDef->numRecords == 0)
    {
        psInfo->bForceEndOfSection = TRUE;
        return NULL;
    }


    if (psInfo->numItems == 0 && psInfo->nCurObjectId == 0)
    {


        psInfo->nTableE00RecLength =
            _AVCE00ComputeRecSize(psTableDef->numFields,
                                  psTableDef->pasFieldDef, FALSE);

        if (psInfo->nBufSize < psInfo->nTableE00RecLength + 1)
        {
            psInfo->nBufSize = psInfo->nTableE00RecLength + 1;
            psInfo->pszBuf = (char*)CPLRealloc(psInfo->pszBuf,
                                               psInfo->nBufSize);
        }


        psInfo->cur.pasFields = (AVCField*)CPLCalloc(psTableDef->numFields,
                                                     sizeof(AVCField));
        for(i=0; i<psTableDef->numFields; i++)
        {
            if (psTableDef->pasFieldDef[i].nType1*10 == AVC_FT_DATE ||
                psTableDef->pasFieldDef[i].nType1*10 == AVC_FT_CHAR ||
                psTableDef->pasFieldDef[i].nType1*10 == AVC_FT_FIXINT ||
                psTableDef->pasFieldDef[i].nType1*10 == AVC_FT_FIXNUM )
            {
                psInfo->cur.pasFields[i].pszStr =
                    (char*)CPLCalloc(psTableDef->pasFieldDef[i].nSize+1,
                                     sizeof(char));
            }
        }

    }

    if (psInfo->numItems == 0)
    {


        memset(psInfo->pszBuf, ' ', psInfo->nTableE00RecLength);
        psInfo->pszBuf[psInfo->nTableE00RecLength] = '\0';


        psInfo->numItems = psInfo->nTableE00RecLength;
        psInfo->iCurItem = 0;
    }


    if (psInfo->iCurItem < psInfo->numItems)
    {


        int nSrcLen, nLenToCopy;

        nSrcLen = strlen(pszLine);
        nLenToCopy = MIN(80, MIN(nSrcLen,(psInfo->numItems-psInfo->iCurItem)));
        strncpy(psInfo->pszBuf+psInfo->iCurItem, pszLine, nLenToCopy);

        psInfo->iCurItem+=80;
    }


    if (psInfo->iCurItem >= psInfo->numItems)
    {


        pasFields = _AVCE00ParseTableRecord(psInfo);

        if (pasFields == NULL)
        {
            CPLError(CE_Failure, CPLE_AppDefined,
                     "Error parsing E00 Table Record: \"%s\"",
                     psInfo->pszBuf);
            return NULL;
        }

        psInfo->numItems = psInfo->iCurItem = 0;
        psInfo->nCurObjectId++;
    }


    if (psInfo->nCurObjectId >= psTableDef->numRecords)
    {
        psInfo->bForceEndOfSection = TRUE;
    }

    return pasFields;
}
