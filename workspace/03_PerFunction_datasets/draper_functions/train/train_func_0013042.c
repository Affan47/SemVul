TestLogs()
{
  struct AllLogsType *pTempLog;
  struct AllLogsType *pPrevLog;
  struct AllLogsType *pNextLog;

  pPrevLog = NULL;
  for (pTempLog = pAllLogs; NULL != pTempLog; pTempLog = pNextLog)
  {
    pNextLog = pTempLog->Next;
    if (NULL == pTempLog->Filter)

    {
      if (pTempLog->LogFile) {
	xfree (pTempLog->LogFile);
      }

      if (NULL == pPrevLog) {
	pAllLogs = pTempLog->Next;
      } else {
	pPrevLog->Next = pTempLog->Next;
      }

      xfree (pTempLog);
    } else {

      pPrevLog = pTempLog;
    }
  }
}
