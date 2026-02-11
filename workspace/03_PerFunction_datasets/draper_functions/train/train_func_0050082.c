tw_reset_device_extension(TW_Device_Extension *tw_dev)
{
	int i = 0;
	struct scsi_cmnd *srb;
	unsigned long flags = 0;

	dprintk(KERN_NOTICE "3w-xxxx: tw_reset_device_extension()\n");

	set_bit(TW_IN_RESET, &tw_dev->flags);
	TW_DISABLE_INTERRUPTS(tw_dev);
	TW_MASK_COMMAND_INTERRUPT(tw_dev);
	spin_lock_irqsave(tw_dev->host->host_lock, flags);


	for (i=0;i<TW_Q_LENGTH;i++) {
		if ((tw_dev->state[i] != TW_S_FINISHED) &&
		    (tw_dev->state[i] != TW_S_INITIAL) &&
		    (tw_dev->state[i] != TW_S_COMPLETED)) {
			srb = tw_dev->srb[i];
			if (srb != NULL) {
				srb->result = (DID_RESET << 16);
				scsi_dma_unmap(srb);
				srb->scsi_done(srb);
			}
		}
	}


	for (i=0;i<TW_Q_LENGTH;i++) {
		tw_dev->free_queue[i] = i;
		tw_dev->state[i] = TW_S_INITIAL;
	}
	tw_dev->free_head = TW_Q_START;
	tw_dev->free_tail = TW_Q_START;
	tw_dev->posted_request_count = 0;
	tw_dev->pending_request_count = 0;
	tw_dev->pending_head = TW_Q_START;
	tw_dev->pending_tail = TW_Q_START;
	tw_dev->reset_print = 0;

	spin_unlock_irqrestore(tw_dev->host->host_lock, flags);

	if (tw_reset_sequence(tw_dev)) {
		printk(KERN_WARNING "3w-xxxx: scsi%d: Reset sequence failed.\n", tw_dev->host->host_no);
		return 1;
	}

	TW_ENABLE_AND_CLEAR_INTERRUPTS(tw_dev);
	clear_bit(TW_IN_RESET, &tw_dev->flags);
	tw_dev->chrdev_request_id = TW_IOCTL_CHRDEV_FREE;

	return 0;
}
