initio_find_done_scb(struct initio_host * host)
{
	struct scsi_ctrl_blk *tmp;

	if ((tmp = host->first_done) != NULL) {
		if ((host->first_done = tmp->next) == NULL)
			host->last_done = NULL;
		tmp->next = NULL;
	}
#if DEBUG_QUEUE
	printk("find done SCB %p; ",tmp);
#endif
	return tmp;
}
