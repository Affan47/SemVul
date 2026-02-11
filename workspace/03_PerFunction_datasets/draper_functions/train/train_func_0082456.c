Curl_file_connect(struct connectdata *conn)
{
  char *real_path = curl_easy_unescape(conn->data, conn->data->reqdata.path, 0, NULL);
  struct FILEPROTO *file;
  int fd;
#if defined(WIN32) || defined(MSDOS) || defined(__EMX__)
  int i;
  char *actual_path;
#endif

  if(!real_path)
    return CURLE_OUT_OF_MEMORY;

  file = (struct FILEPROTO *)calloc(sizeof(struct FILEPROTO), 1);
  if(!file) {
    free(real_path);
    return CURLE_OUT_OF_MEMORY;
  }

  if (conn->data->reqdata.proto.file) {
    free(conn->data->reqdata.proto.file);
  }

  conn->data->reqdata.proto.file = file;

#if defined(WIN32) || defined(MSDOS) || defined(__EMX__)


  actual_path = real_path;
  if ((actual_path[0] == '/') &&
      actual_path[1] &&
      (actual_path[2] == ':' || actual_path[2] == '|'))
  {
    actual_path[2] = ':';
    actual_path++;
  }


  for (i=0; actual_path[i] != '\0'; ++i)
    if (actual_path[i] == '/')
      actual_path[i] = '\\';

  fd = open(actual_path, O_RDONLY | O_BINARY);
  file->path = actual_path;
#else
  fd = open(real_path, O_RDONLY);
  file->path = real_path;
#endif
  file->freepath = real_path;

  file->fd = fd;
  if(!conn->data->set.upload && (fd == -1)) {
    failf(conn->data, "Couldn't open file %s", conn->data->reqdata.path);
    Curl_file_done(conn, CURLE_FILE_COULDNT_READ_FILE, FALSE);
    return CURLE_FILE_COULDNT_READ_FILE;
  }

  return CURLE_OK;
}
