initdecompress(ssh_session session) {
  z_stream *stream = NULL;
  int status;

  stream = malloc(sizeof(z_stream));
  if (stream == NULL) {
    return NULL;
  }
  memset(stream,0,sizeof(z_stream));

  status = inflateInit(stream);
  if (status != Z_OK) {
    SAFE_FREE(stream);
    ssh_set_error(session, SSH_FATAL,
        "Status = %d initiating inflate context!", status);
    return NULL;
  }

  return stream;
}
