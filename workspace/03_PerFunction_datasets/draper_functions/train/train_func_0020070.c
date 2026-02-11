_cupsLangPrintError(const char *prefix,
                    const char *message)
{
  int		bytes;
  int		last_errno;
  char		buffer[2048],
		*bufptr,
		output[8192];
  _cups_globals_t *cg;


  if (!message)
    return;


  last_errno = errno;


  cg = _cupsGlobals();

  if (!cg->lang_default)
    cg->lang_default = cupsLangDefault();


  if (prefix)
  {
    snprintf(buffer, sizeof(buffer), "%s:", prefix);
    bufptr = buffer + strlen(buffer);
  }
  else
    bufptr = buffer;

  snprintf(bufptr, sizeof(buffer) - (bufptr - buffer),

	   _cupsLangString(cg->lang_default, _("%s: %s")),
	   _cupsLangString(cg->lang_default, message), strerror(last_errno));
  strlcat(buffer, "\n", sizeof(buffer));


  bytes = cupsUTF8ToCharset(output, (cups_utf8_t *)buffer, sizeof(output),
                            cg->lang_default->encoding);

  if (bytes > 0)
    fwrite(output, 1, bytes, stderr);
}
