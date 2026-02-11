http_input_stream_free(http_input_stream_t * stream)
{
  if (stream->type == HTTP_TRANSFER_FILE && stream->fd)
  {
    fclose(stream->fd);
    if (stream->deleteOnExit)
      log_info2("Removing '%s'", stream->filename);

  }

  free(stream);
}
