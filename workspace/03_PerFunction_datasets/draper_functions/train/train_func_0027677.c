elv_bio_merged(struct request_queue *q, struct request *rq,
			struct bio *bio)
{
	struct elevator_queue *e = q->elevator;

	if (e->type->ops.elevator_bio_merged_fn)
		e->type->ops.elevator_bio_merged_fn(q, rq, bio);
}
