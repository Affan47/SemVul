load_file(URL U, char *file)
{
  FILE     *fp;
  size_t   len;
  char     *buf;
  char     *filename;
  char     mode[8];

  filename = trim(file);

  memset(mode, '\0', sizeof(mode));
  snprintf(mode, sizeof(mode), "%s", (is_ascii(filename))?"r":"rb");
  fp = fopen(filename, mode);
  if (! fp) {
    NOTIFY(ERROR, "unable to open file: %s", filename );
    return;
  }

  fseek(fp, 0, SEEK_END);
  len = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  buf = (char *)xmalloc(len+1);

  if ((fread(buf, 1, len, fp )) == len) {
    if (is_ascii(filename)) {
      trim(buf);
      len = strlen(buf);
    }
  } else {
    NOTIFY(ERROR, "unable to read file: %s", filename );
  }
  fclose(fp);

  if (len > 0) {
    url_set_conttype(U, get_content_type(filename));
    url_set_postdata(U, buf, len);
  }

  xfree(buf);
  return;
}
