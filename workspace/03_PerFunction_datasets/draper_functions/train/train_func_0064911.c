whcrc_init(struct whcrc *whcrc)
{
	spin_lock_init(&whcrc->irq_lock);
	init_waitqueue_head(&whcrc->cmd_wq);
	INIT_WORK(&whcrc->event_work, whcrc_event_work);
}
