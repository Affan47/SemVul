static_cdata_ml (void *data,
const char *cdata, int length)
{
gamgi_ml *ml = GAMGI_CAST_ML data;
char line[GAMGI_ENGINE_LINE];
int fileline;


fileline = XML_GetCurrentLineNumber (ml->parser);


if (length + 1 > GAMGI_ENGINE_LINE)
  ml->valid = gamgi_io_error_cdata (ml->filename,
  fileline, ml->window);
else
  {
  gamgi_io_token_cut (cdata, line, length + 1);


  if (gamgi_io_token_check (line) == TRUE)
    ml->valid = gamgi_io_error_cdata (ml->filename,
    fileline, ml->window);
  }

}
