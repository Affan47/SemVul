gst_buffer_list_iterator_add_group (GstBufferListIterator * it)
{
  g_return_if_fail (it != NULL);


  while (it->next != NULL && it->next->data != GROUP_START) {
    it->next = g_list_next (it->next);
  }


  if (it->next != NULL) {
    g_queue_insert_before (it->list->buffers, it->next, GROUP_START);
  } else {
    g_queue_push_tail (it->list->buffers, GROUP_START);
  }
}
