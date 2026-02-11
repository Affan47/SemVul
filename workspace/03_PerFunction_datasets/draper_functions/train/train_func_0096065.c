newsnntp_connect(newsnntp * f, mailstream * s)
{
  char * response;
  int r;

  if (f->nntp_stream != NULL)
    return NEWSNNTP_ERROR_BAD_STATE;

  f->nntp_stream = s;

  response = read_line(f);
  if (response == NULL)
    return NEWSNNTP_ERROR_STREAM;

  r = parse_response(f, response);

  switch (r) {
  case 200:
      f->nntp_readonly = FALSE;
      return NEWSNNTP_NO_ERROR;

  case 201:
      f->nntp_readonly = TRUE;
      return NEWSNNTP_NO_ERROR;

  default:
      f->nntp_stream = NULL;
      return NEWSNNTP_ERROR_UNEXPECTED_RESPONSE;
  }
}
