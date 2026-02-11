logErrorFromOS(LogLevel level, const char *str, ...)
{
  if (level > ourLevel)
    return;

#ifndef WIN32
  int err = errno;
#else
  DWORD err = GetLastError();
#endif


  char buf[10000];
  char *bufPtr;
  char *timeStr;
  int timeLen = 0;

  time_t now;


  ourMutex.lock();

  if (ourLoggingTime)
  {
    now = time(NULL);
    timeStr = ctime(&now);
    timeLen = 20;

    strncpy(buf, timeStr, timeLen);
    buf[timeLen] = '\0';
    bufPtr = &buf[timeLen];
  }
  else
    bufPtr = buf;
  va_list ptr;
  va_start(ptr, str);

  vsnprintf(bufPtr, sizeof(buf) - timeLen - 2, str, ptr);
  bufPtr[sizeof(buf) - timeLen - 1] = '\0';


  char bufWithError[10200];

#ifndef WIN32
  const char *errorString = NULL;
  if (err < sys_nerr - 1)
    errorString = sys_errlist[err];
  snprintf(bufWithError, sizeof(bufWithError) - 1, "%s | ErrorFromOSNum: %d ErrorFromOSString: %s", buf, err, errorString);
  bufWithError[sizeof(bufWithError) - 1] = '\0';
#else
  LPVOID errorString = NULL;

  FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        err,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &errorString,
        0, NULL);

  snprintf(bufWithError, sizeof(bufWithError) - 1, "%s | ErrorFromOSNum: %d ErrorFromOSString: %s", buf, err, (char*)errorString);
  bufWithError[sizeof(bufWithError) - 1] = '\0';

  LocalFree(errorString);
#endif


  if (ourType == Colbert)
  {
    if (colbertPrint)
      (*colbertPrint)(ourColbertStream, bufWithError);
  }
  else if (ourFP)
  {
    int written;
    if ((written = fprintf(ourFP, "%s\n", bufWithError)) > 0)
      ourCharsLogged += written;
    fflush(ourFP);
    checkFileSize();
  }
  else if (ourType != None)
  {
    printf("%s\n", bufWithError);
    fflush(stdout);
  }
  if (ourAlsoPrint)
    printf("%s\n", bufWithError);

  invokeFunctor(bufWithError);

#ifndef ARINTERFACE

  if (ourUseAramBehavior && ourFP && ourAramLogSize > 0 &&
      ourCharsLogged > ourAramLogSize)
  {
    filledAramLog();
  }
#endif


#ifdef HAVEATL
  ATLTRACE2("%s\n", buf);
#endif

  va_end(ptr);
  ourMutex.unlock();
}
