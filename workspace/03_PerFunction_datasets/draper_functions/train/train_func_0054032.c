gt_queue_head(GtQueue *q)
{
  gt_assert(q && gt_queue_size(q));
  return q->contents[q->front];
}
