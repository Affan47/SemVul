vfs_get(Vfs_handle *handle, char *key, void **buffer, size_t *length)
{
  int st;
  void *buf;
  size_t len;

  handle->error_msg = NULL;
  handle->error_num = 0;
  log_msg((LOG_TRACE_LEVEL, "vfs_get(%s,%s,\"%s\")",
		   handle->sd->store_name, CTX(handle), key == NULL ? "" : key));

  if ((handle->sw->get)(handle, key, &buf, &len) == -1)
	return(-1);

  st = 0;
  if (handle->get_filter != NULL) {
	void *outbuf;
	size_t outbuf_length;

	log_msg((LOG_TRACE_LEVEL, "get_filter(%s,%s)", CTX(handle), key));
	st = (handle->get_filter)(handle, buf, len, &outbuf, &outbuf_length);
	if (st == -1) {
	  free(buf);
	  return(-1);
	}
	if (st != 0) {
	  free(buf);
	  buf = outbuf;
	  len = outbuf_length;
	}
  }

  *buffer = buf;
  if (length != NULL)
	*length = len;

  return(st);
}
