is_cms_file (const char *fname)
{
  int result;
  FILE *fp;
  char *data;
  size_t datalen;

  fp = fopen (fname, "rb");
  if (!fp)
    return 0;

  data = malloc (CMS_BUFFER_SIZE);
  if (!data)
    {
      fclose (fp);
      return 0;
    }

  datalen = fread (data, 1, CMS_BUFFER_SIZE - 1, fp);
  data[datalen] = 0;
  fclose (fp);

  result = detect_cms (data, datalen);
  free (data);
  return result;
}
