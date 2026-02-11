tur_done(struct scsi_device *sdev, unsigned char *sense)
{
	struct scsi_sense_hdr sshdr;
	int ret;

	ret = scsi_normalize_sense(sense, SCSI_SENSE_BUFFERSIZE, &sshdr);
	if (!ret) {
		sdev_printk(KERN_WARNING, sdev,
			    "%s: sending tur failed, no sense available\n",
			    HP_SW_NAME);
		ret = SCSI_DH_IO;
		goto done;
	}
	switch (sshdr.sense_key) {
	case UNIT_ATTENTION:
		ret = SCSI_DH_IMM_RETRY;
		break;
	case NOT_READY:
		if ((sshdr.asc == 0x04) && (sshdr.ascq == 2)) {


			ret = SCSI_DH_DEV_OFFLINED;
			break;
		}

	default:
		sdev_printk(KERN_WARNING, sdev,
			   "%s: sending tur failed, sense %x/%x/%x\n",
			   HP_SW_NAME, sshdr.sense_key, sshdr.asc,
			   sshdr.ascq);
		break;
	}

done:
	return ret;
}
