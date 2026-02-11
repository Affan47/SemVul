flush()
{
  if( (size_t)(pd_p - pd_buf) != strlen(pd_prefix) ) {
    if (logfunc())
      logfunc()(pd_buf);
    else
      fprintf(logfile, "%s", pd_buf);
  }
  pd_p = pd_buf + strlen(pd_prefix);
  *pd_p = '\0';
}
