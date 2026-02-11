fc_rport_match(struct attribute_container *cont,
			    struct device *dev)
{
	struct Scsi_Host *shost;
	struct fc_internal *i;

	if (!scsi_is_fc_rport(dev))
		return 0;

	shost = dev_to_shost(dev->parent);
	if (!shost->transportt  || shost->transportt->host_attrs.ac.class
	    != &fc_host_class.class)
		return 0;

	i = to_fc_internal(shost->transportt);

	return &i->rport_attr_cont.ac == cont;
}
