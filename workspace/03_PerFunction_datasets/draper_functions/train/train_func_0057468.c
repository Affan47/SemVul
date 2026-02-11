cm_file_CreateLock(CM_FILE *cmfp)
{
  int status;

  if (cmfp == NULL) return eslEINVAL;


  if (!cmfp->syncRead)
    {
      cmfp->syncRead = TRUE;
      status = pthread_mutex_init(&cmfp->readMutex, NULL);
      if (status != 0) goto ERROR;
    }


  if (cmfp->hfp != NULL)
    if((status = p7_hmmfile_CreateLock(cmfp->hfp)) != eslOK) goto ERROR;

  return eslOK;

 ERROR:
  cmfp->syncRead = FALSE;
  return eslFAIL;
}
