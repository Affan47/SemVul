Curl_file_done(struct connectdata *conn,
                        CURLcode status, bool premature)
{
  struct FILEPROTO *file = conn->data->reqdata.proto.file;
  (void)status;
  (void)premature;
  Curl_safefree(file->freepath);

  if(file->fd != -1)
    close(file->fd);

  return CURLE_OK;
}
