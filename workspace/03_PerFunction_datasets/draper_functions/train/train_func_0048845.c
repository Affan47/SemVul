fcoe_ctlr_device_queue_work(struct fcoe_ctlr_device *ctlr,
				       struct work_struct *work)
{
	if (unlikely(!fcoe_ctlr_work_q(ctlr))) {
		printk(KERN_ERR
		       "ERROR: FIP Ctlr '%d' attempted to queue work, "
		       "when no workqueue created.\n", ctlr->id);
		dump_stack();

		return -EINVAL;
	}

	return queue_work(fcoe_ctlr_work_q(ctlr), work);
}
