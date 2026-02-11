SigTermHandler(int a)
{
  struct AllLogsType *pTempLog;

  for (pTempLog = pAllLogs; NULL != pTempLog; pTempLog = pTempLog->Next) {
    data_dump(pTempLog);
    data_clear(pTempLog);
  }
  Exit(0);
}
