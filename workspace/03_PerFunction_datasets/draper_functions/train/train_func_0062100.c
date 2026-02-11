DBFLoadRecord(DBFHandle psDBF, int iRecord) {
  if (psDBF->nCurrentRecord != iRecord) {
    unsigned long nRecordOffset;
    char szMessage[128];

    if (!DBFFlushRecord(psDBF))
      return FALSE;
    nRecordOffset = psDBF->nRecordLength * (unsigned long) iRecord + psDBF->nHeaderLength;
    if (fseek(psDBF->fp, nRecordOffset, SEEK_SET) != 0) {
      sprintf(szMessage, "fseek(%ld) failed on DBF file.\n",(long) nRecordOffset);
      fprintf(stderr,szMessage);
      return FALSE;
    }
    if (fread(psDBF->pszCurrentRecord,psDBF->nRecordLength, 1, psDBF->fp) != 1) {
      sprintf(szMessage, "fread(%d) failed on DBF file.\n",psDBF->nRecordLength);
      fprintf(stderr,szMessage);
      return FALSE;
    }
    psDBF->nCurrentRecord = iRecord;
  }
  return TRUE;
}
