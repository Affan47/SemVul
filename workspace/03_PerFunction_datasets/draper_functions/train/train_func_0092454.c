DSDPFError(void *vobj, const char functionname[], int linen, const char filename[], const char message[], ...)
{
  va_list     Argp;
  int         urank;
  size_t      len;
  char        string[8*1024];

  DSDPFunctionBegin;
  DSDPLogInfoFile = stdout;


  urank = 0;

  va_start(Argp, message);
  sprintf(string, "[%d] DSDP: %s(): Line %d in file %s ", urank,functionname,linen,filename);
  len = strlen(string);

#if defined(DSDP_HAVE_VPRINTF_CHAR)
  vsprintf(string+len, message, (char *) Argp);
#else
  vsprintf(string+len, message, Argp);
#endif
  fprintf(DSDPLogInfoFile, "%s", string);
  fflush(DSDPLogInfoFile);
  if (dsdp_history) {
#if defined(DSDP_HAVE_VPRINTF_CHAR)
    vfprintf(dsdp_history, message, (char *) Argp);
#else
    vfprintf(dsdp_history, message, Argp);
#endif
  }
  va_end(Argp);
  DSDPFunctionReturn(0);
}
