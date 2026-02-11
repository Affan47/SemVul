gegl_buffer_iterator_stop (GeglBufferIterator *iterator)
{
  GeglBufferIterators *i = (gpointer)iterator;
  gint no;
  for (no=0; no<i->iterators;no++)
    {
      gint j;
      gboolean found = FALSE;
      for (j=0; j<no; j++)
        if (i->buffer[no]==i->buffer[j])
          {
            found = TRUE;
            break;
          }
      if (!found)
        gegl_buffer_unlock (i->buffer[no]);
    }

  for (no=0; no<i->iterators; no++)
    {
      if (i->buf[no])
        iterator_buf_pool_release (i->buf[no]);
      i->buf[no]=NULL;
      g_object_unref (i->buffer[no]);
    }
#if DEBUG_DIRECT
  g_print ("%f %f\n", (100.0*direct_read/(in_direct_read+direct_read)),
                           100.0*direct_write/(in_direct_write+direct_write));
#endif
  i->is_finished = TRUE;
  g_slice_free (GeglBufferIterators, i);
}
