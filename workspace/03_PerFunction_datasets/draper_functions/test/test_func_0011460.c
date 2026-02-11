ieee_change_buffer (struct ieee_handle *info, struct ieee_buflist *buflist)
{
  if (buflist->head == NULL)
    {
      struct ieee_buf *buf;

      buf = (struct ieee_buf *) xmalloc (sizeof *buf);
      buf->next = NULL;
      buf->c = 0;
      buflist->head = buf;
      buflist->tail = buf;
    }

  info->current = buflist;
  info->curbuf = buflist->tail;

  return TRUE;
}
