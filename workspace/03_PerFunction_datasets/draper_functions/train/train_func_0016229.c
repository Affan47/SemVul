gst_trace_new (const gchar * filename, gint size)
{
  GstTrace *trace = g_slice_new (GstTrace);

  g_return_val_if_fail (trace != NULL, NULL);
  trace->filename = g_strdup (filename);
  GST_DEBUG ("opening '%s'", trace->filename);
#ifndef S_IWUSR
#define S_IWUSR S_IWRITE
#endif
#ifndef S_IRUSR
#define S_IRUSR S_IREAD
#endif
  trace->fd =
      open (trace->filename, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
  perror ("opening trace file");
  g_return_val_if_fail (trace->fd > 0, NULL);
  trace->buf = g_malloc (size * sizeof (GstTraceEntry));
  g_return_val_if_fail (trace->buf != NULL, NULL);
  trace->bufsize = size;
  trace->bufoffset = 0;

  return trace;
}
