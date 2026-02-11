srp_reconnect_rport(struct srp_rport *rport)
{
	struct Scsi_Host *shost = rport_to_shost(rport);
	struct srp_internal *i = to_srp_internal(shost->transportt);
	struct scsi_device *sdev;
	int res;

	pr_debug("SCSI host %s\n", dev_name(&shost->shost_gendev));

	res = mutex_lock_interruptible(&rport->mutex);
	if (res)
		goto out;
	scsi_target_block(&shost->shost_gendev);
	srp_wait_for_queuecommand(shost);
	res = rport->state != SRP_RPORT_LOST ? i->f->reconnect(rport) : -ENODEV;
	pr_debug("%s (state %d): transport.reconnect() returned %d\n",
		 dev_name(&shost->shost_gendev), rport->state, res);
	if (res == 0) {
		cancel_delayed_work(&rport->fast_io_fail_work);
		cancel_delayed_work(&rport->dev_loss_work);

		rport->failed_reconnects = 0;
		srp_rport_set_state(rport, SRP_RPORT_RUNNING);
		scsi_target_unblock(&shost->shost_gendev, SDEV_RUNNING);


		spin_lock_irq(shost->host_lock);
		__shost_for_each_device(sdev, shost)
			if (sdev->sdev_state == SDEV_OFFLINE)
				sdev->sdev_state = SDEV_RUNNING;
		spin_unlock_irq(shost->host_lock);
	} else if (rport->state == SRP_RPORT_RUNNING) {


		__rport_fail_io_fast(rport);
		scsi_target_unblock(&shost->shost_gendev,
				    SDEV_TRANSPORT_OFFLINE);
		__srp_start_tl_fail_timers(rport);
	} else if (rport->state != SRP_RPORT_BLOCKED) {
		scsi_target_unblock(&shost->shost_gendev,
				    SDEV_TRANSPORT_OFFLINE);
	}
	mutex_unlock(&rport->mutex);

out:
	return res;
}
