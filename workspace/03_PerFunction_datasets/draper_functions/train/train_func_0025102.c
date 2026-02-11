sas_host_release(struct device *dev)
{
	struct Scsi_Host *shost = dev_to_shost(dev);
	struct sas_host_attrs *sas_host = to_sas_host_attrs(shost);
	struct request_queue *q = sas_host->q;

	if (q)
		blk_cleanup_queue(q);
}
