queue_delete (struct QUEUE *q, struct DIR_INFO *d, int pos)
{
  int move, pos2;

  if (pos < q->items) {
    move = q->items - pos - 1;
    pos += q->pos;
    pos2 = pos + 1;

    if (pos >= q->size)
      pos -= q->size;
    d->item[q->base[pos]].queued = 0;

    while (move) {
      if (pos >= q->size)
        pos -= q->size;
      if (pos2 >= q->size)
        pos2 -= q->size;
      q->base[pos++] = q->base[pos2++];
      move--;
    }
    q->items--;
  }
}
