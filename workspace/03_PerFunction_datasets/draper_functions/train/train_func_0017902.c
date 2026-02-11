ctpl_input_stream_read_word (CtplInputStream *stream,
                             const gchar     *accept,
                             gssize           accept_len,
                             gssize           max_len,
                             gsize           *length,
                             GError         **error)
{
  GError   *err = NULL;
  GString  *word;
  gsize     accept_length;
  gsize     max_length;

  accept_length = (accept_len < 0) ? strlen (accept) : (gsize)accept_len;
  max_length = (max_len < 0) ? G_MAXSIZE : (gsize)max_len;
  word = g_string_new (NULL);
  while (! err && word->len <= max_length) {
    gchar c;

    c = ctpl_input_stream_peek_c (stream, &err);
    if (err || ctpl_input_stream_eof_fast (stream) ||
        ! memchr (accept, c, accept_length)) {
      break;
    } else {
      g_string_append_c (word, c);
      ctpl_input_stream_get_c (stream, &err);
    }
  }
  if (err) {
    g_propagate_error (error, err);
  } else {
    if (length) {
      *length = word->len;
    }
  }

  return g_string_free (word, err != NULL);
}
