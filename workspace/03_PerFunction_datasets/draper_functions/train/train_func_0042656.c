scsi_host_queue_ready(struct request_queue *q,
				   struct Scsi_Host *shost,
				   struct scsi_device *sdev)
{
	unsigned int busy;

	if (scsi_host_in_recovery(shost))
		return 0;

	busy = atomic_inc_return(&shost->host_busy) - 1;
	if (atomic_read(&shost->host_blocked) > 0) {
		if (busy)
			goto starved;


		if (atomic_dec_return(&shost->host_blocked) > 0)
			goto out_dec;

		SCSI_LOG_MLQUEUE(3,
			shost_printk(KERN_INFO, shost,
				     "unblocking host at zero depth\n"));
	}

	if (shost->can_queue > 0 && busy >= shost->can_queue)
		goto starved;
	if (shost->host_self_blocked)
		goto starved;


	if (!list_empty(&sdev->starved_entry)) {
		spin_lock_irq(shost->host_lock);
		if (!list_empty(&sdev->starved_entry))
			list_del_init(&sdev->starved_entry);
		spin_unlock_irq(shost->host_lock);
	}

	return 1;

starved:
	spin_lock_irq(shost->host_lock);
	if (list_empty(&sdev->starved_entry))
		list_add_tail(&sdev->starved_entry, &shost->starved_list);
	spin_unlock_irq(shost->host_lock);
out_dec:
	atomic_dec(&shost->host_busy);
	return 0;
}
