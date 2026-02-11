deadline_merged_request(struct request_queue *q,
				    struct request *req, int type)
{
	struct deadline_data *dd = q->elevator->elevator_data;


	if (type == ELEVATOR_FRONT_MERGE) {
		elv_rb_del(deadline_rb_root(dd, req), req);
		deadline_add_rq_rb(dd, req);
	}
}
