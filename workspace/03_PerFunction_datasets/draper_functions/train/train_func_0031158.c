scsi_debug_ioctl(struct scsi_device *dev, int cmd, void __user *arg)
{
	if (SCSI_DEBUG_OPT_NOISE & scsi_debug_opts) {
		if (0x1261 == cmd)
			sdev_printk(KERN_INFO, dev,
				    "%s: BLKFLSBUF [0x1261]\n", __func__);
		else if (0x5331 == cmd)
			sdev_printk(KERN_INFO, dev,
				    "%s: CDROM_GET_CAPABILITY [0x5331]\n",
				    __func__);
		else
			sdev_printk(KERN_INFO, dev, "%s: cmd=0x%x\n",
				    __func__, cmd);
	}
	return -EINVAL;

}
