free_buffer (struct buffer_record *buf)
{
  struct line *l;
  for (l = buf->line_start; l;)
    {
      struct line *n = l->next;
      free (l);
      l = n;
    }
  buf->line_start = NULL;
  free (buf->buffer);
  buf->buffer = NULL;
}
