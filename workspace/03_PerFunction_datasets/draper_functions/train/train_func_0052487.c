gst_trace_text_flush (GstTrace * trace)
{
  int i;

#define STRSIZE (20 + 1 + 10 + 1 + 10 + 1 + 112 + 1 + 1)
  char str[STRSIZE];

  if (!trace) {
    trace = _gst_trace_default;
    if (!trace)
      return;
  }

  for (i = 0; i < trace->bufoffset; i++) {
    g_snprintf (str, STRSIZE, "%20" G_GINT64_FORMAT " %10d %10d %s\n",
        trace->buf[i].timestamp,
        trace->buf[i].sequence, trace->buf[i].data, trace->buf[i].message);
    if (write (trace->fd, str, strlen (str)) < 0) {
      g_warning ("Failed to write trace %d: %s", i, g_strerror (errno));
      return;
    }
  }
  trace->bufoffset = 0;
#undef STRSIZE
}
