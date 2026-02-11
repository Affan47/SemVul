free_buffer_list (GList * list)
{
  GList *g;
  for (g = list; g; g = g_list_next (g)) {
    GstBuffer *buffer = g->data;
    gst_buffer_unref (buffer);
  }
  g_list_free (list);
}
