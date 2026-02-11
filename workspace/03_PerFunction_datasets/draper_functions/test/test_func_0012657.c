read_gzip_header (GInputStream *is,
                  time_t *modification_time)
{
	guchar buffer[GZIP_HEADER_SIZE];
	gssize bytes, to_skip;
	guint mode;
	guint flags;

	bytes = g_input_stream_read (is, buffer, GZIP_HEADER_SIZE,
                               NULL, NULL);
  if (bytes == -1) {
    return FALSE;
  }

	if (bytes != GZIP_HEADER_SIZE)
		return FALSE;

	if (buffer[0] != GZIP_MAGIC_1 || buffer[1] != GZIP_MAGIC_2)
		return FALSE;

	mode = buffer[2];
	if (mode != 8)
		return FALSE;

	flags = buffer[3];

	if (flags & GZIP_FLAG_RESERVED)
		return FALSE;

	if (flags & GZIP_FLAG_EXTRA_FIELD) {
		guchar tmp[2];

    bytes = g_input_stream_read (is, tmp, 2, NULL, NULL);

    if (bytes != 2) {
			return FALSE;
    }

    to_skip = tmp[0] | (tmp[0] << 8);
    bytes = g_input_stream_skip (is, to_skip, NULL, NULL);
    if (bytes != to_skip) {
      return FALSE;
    }
	}

	if (flags & GZIP_FLAG_ORIG_NAME) {
    if (!skip_string (is)) {
      return FALSE;
    }
  }

	if (flags & GZIP_FLAG_COMMENT) {
    if (!skip_string (is)) {
      return FALSE;
    }
  }

	if (flags & GZIP_FLAG_HEAD_CRC) {
    bytes = g_input_stream_skip (is, 2, NULL, NULL);
		if (bytes != 2) {
      return FALSE;
    }
  }

  *modification_time = (buffer[4] | (buffer[5] << 8)
                        | (buffer[6] << 16) | (buffer[7] << 24));

	return TRUE;
}
