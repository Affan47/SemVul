set_ioaccel2_performant_mode(struct ctlr_info *h,
						struct CommandList *c,
						int reply_queue)
{
	struct io_accel2_cmd *cp = &h->ioaccel2_cmd_pool[c->cmdindex];


	if (likely(reply_queue == DEFAULT_REPLY_QUEUE))
		cp->reply_queue = smp_processor_id() % h->nreply_queues;
	else
		cp->reply_queue = reply_queue % h->nreply_queues;


	c->busaddr |= (h->ioaccel2_blockFetchTable[cp->sg_count]);
}
