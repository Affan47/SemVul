save_buffer_to_temp(char *buf, size_t buflen)
{
  int st;
  char *filename;
  size_t len;
  FILE *fp;

  if ((filename = create_temp_filename(NULL)) == NULL)
	return(NULL);

  if ((fp = create_temp_file(filename)) == NULL)
	return(NULL);

  if (buflen == 0)
	len = strlen(buf);
  else
	len = buflen;

  st = write_buffer(fileno(fp), buf, len);

  fclose(fp);

  return(st == -1 ? NULL : filename);
}
