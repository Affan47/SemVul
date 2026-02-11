gst_buffer_list_iterator_remove (GstBufferListIterator * it)
{
  g_return_if_fail (it != NULL);
  g_return_if_fail (it->last_returned != NULL);
  g_assert (it->last_returned->data != GROUP_START);

  if (it->last_returned->data != STOLEN) {
    gst_buffer_unref (it->last_returned->data);
  }
  g_queue_delete_link (it->list->buffers, it->last_returned);
  it->last_returned = NULL;
}
