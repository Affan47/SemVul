rfc959_chmod (gftp_request * request, const char *file, mode_t mode)
{
  char *tempstr, *utf8;
  size_t destlen;
  int ret;

  g_return_val_if_fail (request != NULL, GFTP_EFATAL);
  g_return_val_if_fail (file != NULL, GFTP_EFATAL);
  g_return_val_if_fail (request->datafd > 0, GFTP_EFATAL);

  utf8 = gftp_filename_from_utf8 (request, file, &destlen);
  if (utf8 != NULL)
    {
      tempstr = g_strdup_printf ("SITE CHMOD %o %s\r\n", mode, utf8);
      g_free (utf8);
    }
  else
    tempstr = g_strdup_printf ("SITE CHMOD %o %s\r\n", mode, file);

  ret = rfc959_send_command (request, tempstr, -1, 1, 0);
  g_free (tempstr);

  if (ret < 0)
    return (ret);
  else if (ret == '2')
    return (0);
  else
    return (GFTP_ERETRYABLE);
}
