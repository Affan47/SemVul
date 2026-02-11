fcoe_destroy_work(struct work_struct *work)
{
	struct fcoe_ctlr_device *cdev;
	struct fcoe_ctlr *ctlr;
	struct fcoe_port *port;
	struct fcoe_interface *fcoe;
	struct Scsi_Host *shost;
	struct fc_host_attrs *fc_host;
	unsigned long flags;
	struct fc_vport *vport;
	struct fc_vport *next_vport;

	port = container_of(work, struct fcoe_port, destroy_work);
	shost = port->lport->host;
	fc_host = shost_to_fc_host(shost);


	spin_lock_irqsave(shost->host_lock, flags);
	list_for_each_entry_safe(vport, next_vport, &fc_host->vports, peers) {
		if (vport->flags & (FC_VPORT_DEL | FC_VPORT_CREATING)) {
			continue;
		} else {
			vport->flags |= FC_VPORT_DELETING;
			queue_work(fc_host_work_q(shost),
				   &vport->vport_delete_work);
		}
	}
	spin_unlock_irqrestore(shost->host_lock, flags);

	flush_workqueue(fc_host_work_q(shost));

	mutex_lock(&fcoe_config_mutex);

	fcoe = port->priv;
	ctlr = fcoe_to_ctlr(fcoe);
	cdev = fcoe_ctlr_to_ctlr_dev(ctlr);

	fcoe_if_destroy(port->lport);
	fcoe_interface_cleanup(fcoe);

	mutex_unlock(&fcoe_config_mutex);

	fcoe_ctlr_device_delete(cdev);
}
