gst_alloc_trace_get (const gchar * name)
{
  GList *walk = _gst_alloc_tracers;

  g_return_val_if_fail (name, NULL);

  while (walk) {
    GstAllocTrace *trace = (GstAllocTrace *) walk->data;

    if (!strcmp (trace->name, name))
      return trace;

    walk = g_list_next (walk);
  }
  return NULL;
}
