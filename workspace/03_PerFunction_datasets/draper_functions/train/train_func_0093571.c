StrError(int errnum) {
  const int MaxErrStrLen = 2000;
  char buffer[MaxErrStrLen];
  buffer[0] = '\0';
  char* str = buffer;
#ifdef HAVE_STRERROR_R

  if (errnum)
# if defined(__GLIBC__) && defined(_GNU_SOURCE)


    str = strerror_r(errnum,buffer,MaxErrStrLen-1);
# else
    strerror_r(errnum,buffer,MaxErrStrLen-1);
# endif
#elif defined(HAVE_STRERROR_S)
    if (errnum)
      strerror_s(buffer, errnum);
#elif defined(HAVE_STRERROR)


  if (errnum)
    strncpy(buffer,strerror(errnum),MaxErrStrLen-1);
  buffer[MaxErrStrLen-1] = '\0';
#else


  sprintf(buffer, "Error #%d", errnum);
#endif
  return str;
}
