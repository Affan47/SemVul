_sshv2_generate_utf8_path (gftp_request * request, const char *str, size_t *len)
{
  char *path, *utf8;

  if (*str == '/')
    path = g_strdup (str);
  else
    path = gftp_build_path (request, request->directory, str, NULL);

  utf8 = gftp_filename_from_utf8 (request, path, len);
  if (utf8 != NULL)
    {
      g_free (path);
      return (utf8);
    }
  else
    {
      *len = strlen (path);
      return (path);
    }
}
