send_signaling(struct chan_iax2_pvt *pvt)
{
	struct signaling_queue_entry *s = NULL;

	while ((s = AST_LIST_REMOVE_HEAD(&pvt->signaling_queue, next))) {
		iax2_send(pvt, &s->f, 0, -1, 0, 0, 0);
		free_signaling_queue_entry(s);
	}
	pvt->hold_signaling = 0;
}
