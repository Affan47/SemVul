__ata_scsi_queuecmd(struct scsi_cmnd *scmd,
				      struct ata_device *dev)
{
	u8 scsi_op = scmd->cmnd[0];
	ata_xlat_func_t xlat_func;
	int rc = 0;

	if (dev->class == ATA_DEV_ATA || dev->class == ATA_DEV_ZAC) {
		if (unlikely(!scmd->cmd_len || scmd->cmd_len > dev->cdb_len))
			goto bad_cdb_len;

		xlat_func = ata_get_xlat_func(dev, scsi_op);
	} else {
		if (unlikely(!scmd->cmd_len))
			goto bad_cdb_len;

		xlat_func = NULL;
		if (likely((scsi_op != ATA_16) || !atapi_passthru16)) {

			int len = COMMAND_SIZE(scsi_op);
			if (unlikely(len > scmd->cmd_len || len > dev->cdb_len))
				goto bad_cdb_len;

			xlat_func = atapi_xlat;
		} else {

			if (unlikely(scmd->cmd_len > 16))
				goto bad_cdb_len;

			xlat_func = ata_get_xlat_func(dev, scsi_op);
		}
	}

	if (xlat_func)
		rc = ata_scsi_translate(dev, scmd, xlat_func);
	else
		ata_scsi_simulate(dev, scmd);

	return rc;

 bad_cdb_len:
	DPRINTK("bad CDB len=%u, scsi_op=0x%02x, max=%u\n",
		scmd->cmd_len, scsi_op, dev->cdb_len);
	scmd->result = DID_ERROR << 16;
	scmd->scsi_done(scmd);
	return 0;
}
