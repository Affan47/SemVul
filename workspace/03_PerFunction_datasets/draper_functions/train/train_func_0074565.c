fc_rport_final_delete(struct work_struct *work)
{
	struct fc_rport *rport =
		container_of(work, struct fc_rport, rport_delete_work);
	struct device *dev = &rport->dev;
	struct Scsi_Host *shost = rport_to_shost(rport);
	struct fc_internal *i = to_fc_internal(shost->transportt);
	unsigned long flags;
	int do_callback = 0;

	fc_terminate_rport_io(rport);


	if (rport->flags & FC_RPORT_SCAN_PENDING)
		scsi_flush_work(shost);


	spin_lock_irqsave(shost->host_lock, flags);
	if (rport->flags & FC_RPORT_DEVLOSS_PENDING) {
		spin_unlock_irqrestore(shost->host_lock, flags);
		if (!cancel_delayed_work(&rport->fail_io_work))
			fc_flush_devloss(shost);
		if (!cancel_delayed_work(&rport->dev_loss_work))
			fc_flush_devloss(shost);
		cancel_work_sync(&rport->scan_work);
		spin_lock_irqsave(shost->host_lock, flags);
		rport->flags &= ~FC_RPORT_DEVLOSS_PENDING;
	}
	spin_unlock_irqrestore(shost->host_lock, flags);


	if (rport->scsi_target_id != -1)
		fc_starget_delete(&rport->stgt_delete_work);


	spin_lock_irqsave(shost->host_lock, flags);
	if (!(rport->flags & FC_RPORT_DEVLOSS_CALLBK_DONE) &&
	    (i->f->dev_loss_tmo_callbk)) {
		rport->flags |= FC_RPORT_DEVLOSS_CALLBK_DONE;
		do_callback = 1;
	}
	spin_unlock_irqrestore(shost->host_lock, flags);

	if (do_callback)
		i->f->dev_loss_tmo_callbk(rport);

	fc_bsg_remove(rport->rqst_q);

	transport_remove_device(dev);
	device_del(dev);
	transport_destroy_device(dev);
	put_device(&shost->shost_gendev);
	put_device(dev);
}
