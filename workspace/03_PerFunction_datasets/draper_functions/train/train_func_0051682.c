DBFReadAttribute(DBFHandle psDBF, int hEntity, int iField,
                              char chReqType )

{
    int	       	nRecordOffset;
    uchar	*pabyRec;
    void	*pReturnField = NULL;

    static double dDoubleField;


    if( hEntity < 0 || hEntity >= psDBF->nRecords )
        return( NULL );

    if( psDBF->nCurrentRecord != hEntity )
    {
	DBFFlushRecord( psDBF );

	nRecordOffset = psDBF->nRecordLength * hEntity + psDBF->nHeaderLength;

	fseek( psDBF->fp, nRecordOffset, 0 );
	fread( psDBF->pszCurrentRecord, psDBF->nRecordLength, 1, psDBF->fp );

	psDBF->nCurrentRecord = hEntity;
    }

    pabyRec = (uchar *) psDBF->pszCurrentRecord;


    if( psDBF->panFieldSize[iField]+1 > nStringFieldLen )
    {
	nStringFieldLen = psDBF->panFieldSize[iField]*2 + 10;
	pszStringField = (char *) SfRealloc(pszStringField,nStringFieldLen);
    }


    strncpy( pszStringField, (const char*)pabyRec+psDBF->panFieldOffset[iField],
	     psDBF->panFieldSize[iField] );
    pszStringField[psDBF->panFieldSize[iField]] = '\0';

    pReturnField = pszStringField;


    if( chReqType == 'N' )
    {
        dDoubleField = atof(pszStringField);

	pReturnField = &dDoubleField;
    }


#ifdef TRIM_DBF_WHITESPACE
    else
    {
        char	*pchSrc, *pchDst;

        pchDst = pchSrc = pszStringField;
        while( *pchSrc == ' ' )
            pchSrc++;

        while( *pchSrc != '\0' )
            *(pchDst++) = *(pchSrc++);
        *pchDst = '\0';

        while( *(--pchDst) == ' ' && pchDst != pszStringField )
            *pchDst = '\0';

    }
#endif

    return( pReturnField );
}
