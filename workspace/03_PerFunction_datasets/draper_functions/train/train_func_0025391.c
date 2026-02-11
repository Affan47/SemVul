store_fc_private_host_tgtid_bind_type(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	struct Scsi_Host *shost = transport_class_to_shost(dev);
	struct fc_rport *rport;
 	enum fc_tgtid_binding_type val;
	unsigned long flags;

	if (get_fc_tgtid_bind_type_match(buf, &val))
		return -EINVAL;


	if (val != fc_host_tgtid_bind_type(shost)) {
		spin_lock_irqsave(shost->host_lock, flags);
		while (!list_empty(&fc_host_rport_bindings(shost))) {
			get_list_head_entry(rport,
				&fc_host_rport_bindings(shost), peers);
			list_del(&rport->peers);
			rport->port_state = FC_PORTSTATE_DELETED;
			fc_queue_work(shost, &rport->rport_delete_work);
		}
		spin_unlock_irqrestore(shost->host_lock, flags);
	}

	fc_host_tgtid_bind_type(shost) = val;
	return count;
}
