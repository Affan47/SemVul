encapsulated_reader(sockreader_t * self, char **buf,
                                 apr_size_t *len, const char *enc_info,
				 const char *preview) {
  char *read;
  char *read2;
  char *last;
  char *cur;
  char *key;
  char *val;
  char *tmp;
  apr_status_t status;
  apr_size_t size;
  apr_size_t size2;

  tmp = apr_pstrdup(self->pool, enc_info);
  cur = apr_strtok(tmp, ",", &last);
  val = cur;
  while (cur) {
    val = cur;
    cur = apr_strtok(NULL, ", ", &last);
  }

  if (!val) {
    return APR_EINVAL;
  }

  key = apr_strtok(val, "=", &last);
  val = apr_strtok(NULL, "=", &last);

  if (!key || !val) {
    return APR_EINVAL;
  }

  size = apr_atoi64(val);

  if (size == 0) {
    return APR_SUCCESS;
  }

  if (self->options & SOCKREADER_OPTIONS_IGNORE_BODY) {
    read = NULL;
  }
  else {
    read = apr_pcalloc(self->pool, size);
  }
  sockreader_read_block(self, read, &size);

  if (strcasecmp(key, "null-body") != 0 && (!preview || strcasecmp(preview, "0") != 0)) {
    if ((status = transfer_enc_reader(self, &read2, &size2, "chunked"))
	!= APR_SUCCESS) {
      return status;
    }
    if (!self->options & SOCKREADER_OPTIONS_IGNORE_BODY) {
      *buf = apr_pcalloc(self->pool, size + size2);
      memcpy(*buf, read, size);
      memcpy(&(*buf)[size], read2, size2);
      *len = size + size2;
    }
  }
  else {
    *len = size;
    *buf = read;
  }

  if (self->options & SOCKREADER_OPTIONS_IGNORE_BODY) {
    *len = 0;
  }

  return APR_SUCCESS;
}
