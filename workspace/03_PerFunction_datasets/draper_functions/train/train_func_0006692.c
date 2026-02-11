DisplayMessage(FILE * pOut, const char *fmt, ...) {
  va_list ap;
  va_start(ap,fmt);
  if (pOut == NULL || pOut == stdout) {
    g_pConsole->VPrintf(fmt, ap);
  }
  else {
    vfprintf(pOut, fmt, ap);
  }
  va_end(ap);
}
