log_close()
{
  pthread_mutex_destroy(&gFileMutex);

  if(gLogFile_FILE != stdout)
    fclose(gLogFile_FILE);
}
