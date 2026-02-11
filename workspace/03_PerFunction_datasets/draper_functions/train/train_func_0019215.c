slurmdbd_free_job_start_msg(void *in)
{
	dbd_job_start_msg_t *msg = (dbd_job_start_msg_t *)in;
	if (msg) {
		xfree(msg->account);
		xfree(msg->block_id);
		xfree(msg->gres_alloc);
		xfree(msg->gres_req);
		xfree(msg->gres_used);
		xfree(msg->name);
		xfree(msg->nodes);
		xfree(msg->node_inx);
		xfree(msg->partition);
		xfree(msg->wckey);
		xfree(msg);
	}
}
