is_sentinel(struct queue *q, struct list_head *h)
{
	return (h >= q->sentinels) && (h < (q->sentinels + NR_SENTINELS));
}
