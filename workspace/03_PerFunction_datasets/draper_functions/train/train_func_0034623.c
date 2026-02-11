ata_set_max_sectors(struct ata_device *dev, u64 new_sectors)
{
	unsigned int err_mask;
	struct ata_taskfile tf;
	int lba48 = ata_id_has_lba48(dev->id);

	new_sectors--;

	ata_tf_init(dev, &tf);

	tf.flags |= ATA_TFLAG_DEVICE | ATA_TFLAG_ISADDR;

	if (lba48) {
		tf.command = ATA_CMD_SET_MAX_EXT;
		tf.flags |= ATA_TFLAG_LBA48;

		tf.hob_lbal = (new_sectors >> 24) & 0xff;
		tf.hob_lbam = (new_sectors >> 32) & 0xff;
		tf.hob_lbah = (new_sectors >> 40) & 0xff;
	} else {
		tf.command = ATA_CMD_SET_MAX;

		tf.device |= (new_sectors >> 24) & 0xf;
	}

	tf.protocol |= ATA_PROT_NODATA;
	tf.device |= ATA_LBA;

	tf.lbal = (new_sectors >> 0) & 0xff;
	tf.lbam = (new_sectors >> 8) & 0xff;
	tf.lbah = (new_sectors >> 16) & 0xff;

	err_mask = ata_exec_internal(dev, &tf, NULL, DMA_NONE, NULL, 0, 0);
	if (err_mask) {
		ata_dev_warn(dev,
			     "failed to set max address (err_mask=0x%x)\n",
			     err_mask);
		if (err_mask == AC_ERR_DEV &&
		    (tf.feature & (ATA_ABORTED | ATA_IDNF)))
			return -EACCES;
		return -EIO;
	}

	return 0;
}
