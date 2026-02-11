cupsGetPPD(const char *name)
{
  _cups_globals_t *cg = _cupsGlobals();
  time_t	modtime = 0;


  cg->ppd_filename[0] = '\0';

  if (cupsGetPPD3(CUPS_HTTP_DEFAULT, name, &modtime, cg->ppd_filename,
                  sizeof(cg->ppd_filename)) == HTTP_STATUS_OK)
    return (cg->ppd_filename);
  else
    return (NULL);
}
