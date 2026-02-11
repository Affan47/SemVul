blk_queue_max_segments(struct request_queue *q, unsigned short max_segments)
{
	if (!max_segments) {
		max_segments = 1;
		printk(KERN_INFO "%s: set to minimum %d\n",
		       __func__, max_segments);
	}

	q->limits.max_segments = max_segments;
}
