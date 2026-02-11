do_multiply_string (const gchar  *str,
                    glong         n,
                    GError      **error)
{
  gchar *buf = NULL;

  if (n < 1) {
    buf = g_strdup ("");
  } else if (n == 1) {
    buf = g_strdup (str);
  } else {
    gsize       buf_len;
    gsize       str_len;
    gsize       i, j;

    str_len = strlen (str);


    if (G_UNLIKELY ((str_len > 0 && (gsize)n > G_MAXSIZE / str_len) ||
                    str_len * (gsize)n >= G_MAXSIZE)) {
      g_set_error (error, CTPL_EVAL_ERROR, CTPL_EVAL_ERROR_FAILED,
                   "String multiplication would overflow allocating "
                   "%"G_GSIZE_FORMAT"*%"G_GSIZE_FORMAT"+1 bytes",
                   (gsize)n, str_len);
    } else {
      buf_len = str_len * (gsize)n;
      buf = g_try_malloc (buf_len + 1);
      if (G_UNLIKELY (! buf)) {
        g_set_error (error, CTPL_EVAL_ERROR, CTPL_EVAL_ERROR_FAILED,
                     "Cannot allocate %"G_GSIZE_FORMAT" bytes for string "
                     "multiplication", buf_len + 1);
      } else {
        for (i = 0; i < (gsize)n; i++) {
          for (j = 0; j < str_len; j++) {
            buf[str_len * i + j] = str[j];
          }
        }
        buf[buf_len] = 0;
      }
    }
  }

  return buf;
}
