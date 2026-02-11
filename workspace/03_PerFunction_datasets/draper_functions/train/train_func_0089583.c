_partial_free_dbd_job_start(void *object)
{
	dbd_job_start_msg_t *req = (dbd_job_start_msg_t *)object;
	if (req) {
		xfree(req->account);
		xfree(req->block_id);
		xfree(req->name);
		xfree(req->nodes);
		xfree(req->partition);
		xfree(req->node_inx);
		xfree(req->wckey);
		xfree(req->gres_alloc);
		xfree(req->gres_req);
		xfree(req->gres_used);
	}
}
