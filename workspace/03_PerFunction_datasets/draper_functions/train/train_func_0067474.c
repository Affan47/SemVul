mega_del_logdrv(adapter_t *adapter, int logdrv)
{
	unsigned long flags;
	scb_t *scb;
	int rval;


	atomic_set(&adapter->quiescent, 1);


	while (atomic_read(&adapter->pend_cmds) > 0 ||
	       !list_empty(&adapter->pending_list))
		msleep(1000);

	rval = mega_do_del_logdrv(adapter, logdrv);

	spin_lock_irqsave(&adapter->lock, flags);


	if (adapter->read_ldidmap) {
		struct list_head *pos;
		list_for_each(pos, &adapter->pending_list) {
			scb = list_entry(pos, scb_t, list);
			if (scb->pthru->logdrv < 0x80 )
				scb->pthru->logdrv += 0x80;
		}
	}

	atomic_set(&adapter->quiescent, 0);

	mega_runpendq(adapter);

	spin_unlock_irqrestore(&adapter->lock, flags);

	return rval;
}
