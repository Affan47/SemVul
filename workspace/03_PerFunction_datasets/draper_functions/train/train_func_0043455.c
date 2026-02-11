local_get_file_size (gftp_request * request, const char *filename)
{
  struct stat st;
  size_t destlen;
  char *utf8;
  int ret;

  utf8 = gftp_filename_from_utf8 (request, filename, &destlen);
  if (utf8 != NULL)
    {
      ret = stat (utf8, &st);
      g_free (utf8);
    }
  else
    ret = stat (filename, &st);

  if (ret == -1)
    return (GFTP_ERETRYABLE);

  return (st.st_size);
}
