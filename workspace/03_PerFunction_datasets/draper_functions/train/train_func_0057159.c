aoeblk_request(struct request_queue *q)
{
	struct aoedev *d;
	struct request *rq;

	d = q->queuedata;
	if ((d->flags & DEVFL_UP) == 0) {
		pr_info_ratelimited("aoe: device %ld.%d is not up\n",
			d->aoemajor, d->aoeminor);
		while ((rq = blk_peek_request(q))) {
			blk_start_request(rq);
			aoe_end_request(d, rq, 1);
		}
		return;
	}
	aoecmd_work(d);
}
