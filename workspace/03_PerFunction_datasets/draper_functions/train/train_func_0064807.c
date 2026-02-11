mbuf_free (struct mbuf_set *ms)
{
  if (ms)
    {
      int i;
      for (i = 0; i < (int) ms->len; ++i)
	{
	  struct mbuf_item *item = &ms->array[MBUF_INDEX(ms->head, i, ms->capacity)];
	  mbuf_free_buf (item->buffer);
	}
      free (ms->array);
      mutex_destroy (&ms->mutex);
      free (ms);
    }
}
