LSL_loadLib(const char *libName, char *msgBuf, int msgLen)
{
  soHandle_t h=NULL;

#ifdef ERROR_LOADLIB
  mysnprintf(msgBuf, msgLen, "loadLib error: Do not know how to handle shared libraries on this operating system");
  return h;
#else

  if (libName==NULL) {
    mysnprintf(msgBuf, msgLen, "loadLib error: no library name given (libName is NULL)");
    return NULL;
  }

# ifdef HAVE_WINDOWS_H
  h = LoadLibrary (libName);
  if (NULL == h) {
    mysnprintf(msgBuf, msgLen, "Windows error while loading dynamic library %s, error = %d.\n(see http://msdn.microsoft.com/en-us/library/ms681381%%28v=vs.85%%29.aspx)\n", libName, GetLastError());
  }
# else
  h = dlopen (libName, RTLD_NOW);
  if (NULL == h) {
    strncpy(msgBuf, dlerror(), msgLen);
    msgBuf[msgLen-1]=0;
  }
# endif

  return h;
#endif
}
