gst_buffer_list_n_groups (GstBufferList * list)
{
  GList *tmp;
  guint n;

  g_return_val_if_fail (list != NULL, 0);

  tmp = list->buffers->head;
  n = 0;
  while (tmp) {
    if (tmp->data == GROUP_START) {
      n++;
    }
    tmp = g_list_next (tmp);
  }

  return n;
}
