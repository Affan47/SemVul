hpsa_ioctl(struct scsi_device *dev, int cmd, void __user *arg)
{
	struct ctlr_info *h;
	void __user *argp = (void __user *)arg;
	int rc;

	h = sdev_to_hba(dev);

	switch (cmd) {
	case CCISS_DEREGDISK:
	case CCISS_REGNEWDISK:
	case CCISS_REGNEWD:
		hpsa_scan_start(h->scsi_host);
		return 0;
	case CCISS_GETPCIINFO:
		return hpsa_getpciinfo_ioctl(h, argp);
	case CCISS_GETDRIVVER:
		return hpsa_getdrivver_ioctl(h, argp);
	case CCISS_PASSTHRU:
		if (atomic_dec_if_positive(&h->passthru_cmds_avail) < 0)
			return -EAGAIN;
		rc = hpsa_passthru_ioctl(h, argp);
		atomic_inc(&h->passthru_cmds_avail);
		return rc;
	case CCISS_BIG_PASSTHRU:
		if (atomic_dec_if_positive(&h->passthru_cmds_avail) < 0)
			return -EAGAIN;
		rc = hpsa_big_passthru_ioctl(h, argp);
		atomic_inc(&h->passthru_cmds_avail);
		return rc;
	default:
		return -ENOTTY;
	}
}
