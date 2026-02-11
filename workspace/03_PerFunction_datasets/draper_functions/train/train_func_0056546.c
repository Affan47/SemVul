DBFReadTuple(DBFHandle psDBF, int hEntity)
{
    int nRecordOffset;
    unsigned char *pabyRec;
    static char *pReturnTuple = NULL;

    static int nTupleLen = 0;


    if (hEntity < 0 || hEntity >= psDBF->nRecords)
	return (NULL);

    if (psDBF->nCurrentRecord != hEntity) {
	DBFFlushRecord(psDBF);

	nRecordOffset =
	    psDBF->nRecordLength * hEntity + psDBF->nHeaderLength;

	fseek(psDBF->fp, nRecordOffset, 0);
	if (! fread(psDBF->pszCurrentRecord, psDBF->nRecordLength, 1, psDBF->fp)) {

	}

	psDBF->nCurrentRecord = hEntity;
    }

    pabyRec = (unsigned char *) psDBF->pszCurrentRecord;

    if (nTupleLen < psDBF->nRecordLength) {
	nTupleLen = psDBF->nRecordLength;
	pReturnTuple =
	    (char *) SfRealloc(pReturnTuple, psDBF->nRecordLength);
    }

    memcpy(pReturnTuple, pabyRec, psDBF->nRecordLength);

    return (pReturnTuple);
}
