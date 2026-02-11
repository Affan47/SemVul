audioresample_buffer_queue_pull (AudioresampleBufferQueue * queue, int length)
{
  GList *g;
  AudioresampleBuffer *newbuffer;
  AudioresampleBuffer *buffer;
  AudioresampleBuffer *subbuffer;

  g_return_val_if_fail (length > 0, NULL);

  if (queue->depth < length) {
    return NULL;
  }

  RESAMPLE_LOG ("pulling %d, %d available", length, queue->depth);

  g = g_list_first (queue->buffers);
  buffer = g->data;

  if (buffer->length > length) {
    newbuffer = audioresample_buffer_new_subbuffer (buffer, 0, length);

    subbuffer = audioresample_buffer_new_subbuffer (buffer, length,
        buffer->length - length);
    g->data = subbuffer;
    audioresample_buffer_unref (buffer);
  } else {
    int offset = 0;

    newbuffer = audioresample_buffer_new_and_alloc (length);

    while (offset < length) {
      g = g_list_first (queue->buffers);
      buffer = g->data;

      if (buffer->length > length - offset) {
        int n = length - offset;

        memcpy (newbuffer->data + offset, buffer->data, n);
        subbuffer =
            audioresample_buffer_new_subbuffer (buffer, n, buffer->length - n);
        g->data = subbuffer;
        audioresample_buffer_unref (buffer);
        offset += n;
      } else {
        memcpy (newbuffer->data + offset, buffer->data, buffer->length);

        queue->buffers = g_list_delete_link (queue->buffers, g);
        offset += buffer->length;
        audioresample_buffer_unref (buffer);
      }
    }
  }

  queue->depth -= length;
  queue->offset += length;

  return newbuffer;
}
