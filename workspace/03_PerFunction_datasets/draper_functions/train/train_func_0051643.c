buf_empty(struct buf_head *h)
{
  struct buf_chunk *chunk, *next;
  for (chunk = h->head; chunk; chunk = next) {
    next = chunk->next;
    xfree(chunk);
  }
  h->head     = NULL;
  h->tail     = NULL;
  h->used     = 0;
  h->checksum = 0;
}
