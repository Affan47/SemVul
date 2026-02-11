storvsc_remove(struct hv_device *dev)
{
	struct storvsc_device *stor_device = hv_get_drvdata(dev);
	struct Scsi_Host *host = stor_device->host;

#if IS_ENABLED(CONFIG_SCSI_FC_ATTRS)
	if (host->transportt == fc_transport_template)
		fc_remove_host(host);
#endif
	scsi_remove_host(host);
	storvsc_dev_remove(dev);
	scsi_host_put(host);

	return 0;
}
