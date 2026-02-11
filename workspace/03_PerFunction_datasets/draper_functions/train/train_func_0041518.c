http_input_stream_new_from_file(const char *filename)
{
  http_input_stream_t *result;
  FILE *fd;

  char err_buf[256];
  if (!(fd = fopen(filename, "rb"))) {
    strerror_r(errno, err_buf, sizeof(err_buf));
    log_error2("fopen failed (%s)", err_buf);
    return NULL;
  }


  if (!(result = (http_input_stream_t *) malloc(sizeof(http_input_stream_t))))
  {
    log_error1("malloc failed");
    fclose(fd);
    return NULL;
  }

  result->type = HTTP_TRANSFER_FILE;
  result->fd = fd;
  result->deleteOnExit = 0;
  strcpy(result->filename, filename);

  return result;
}
