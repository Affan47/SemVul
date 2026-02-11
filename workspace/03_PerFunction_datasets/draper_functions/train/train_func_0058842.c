rfc959_read_response (gftp_request * request, int disconnect_on_42x)
{
  char tempstr[255], code[4];
  rfc959_parms * parms;
  ssize_t num_read;

  g_return_val_if_fail (request != NULL, GFTP_EFATAL);
  g_return_val_if_fail (request->datafd > 0, GFTP_EFATAL);

  *code = '\0';
  if (request->last_ftp_response)
    {
      g_free (request->last_ftp_response);
      request->last_ftp_response = NULL;
    }

  parms = request->protocol_data;

  do
    {
      if ((num_read = gftp_get_line (request, &parms->datafd_rbuf, tempstr,
                                     sizeof (tempstr), request->datafd)) <= 0)
	break;

      if (isdigit ((int) *tempstr) && isdigit ((int) *(tempstr + 1))
	  && isdigit ((int) *(tempstr + 2)))
	{
	  strncpy (code, tempstr, 3);
	  code[3] = ' ';
	}

      if (*tempstr == '4' || *tempstr == '5')
        request->logging_function (gftp_logging_error, request,
  				   "%s\n", tempstr);
      else
        request->logging_function (gftp_logging_recv, request,
  				   "%s\n", tempstr);
    }
  while (strncmp (code, tempstr, 4) != 0);

  if (num_read < 0)
    return ((int) num_read);

  request->last_ftp_response = g_strdup (tempstr);

  if (request->last_ftp_response[0] == '4' &&
      request->last_ftp_response[1] == '2' &&
      disconnect_on_42x)
    {
      gftp_disconnect (request);
      return (GFTP_ETIMEDOUT);
    }

  return (*request->last_ftp_response);
}
