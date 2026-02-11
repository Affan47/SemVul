qla4xxx_set_flash(struct scsi_qla_host *ha, dma_addr_t dma_addr,
		      uint32_t offset, uint32_t length, uint32_t options)
{
	uint32_t mbox_cmd[MBOX_REG_COUNT];
	uint32_t mbox_sts[MBOX_REG_COUNT];
	int status = QLA_SUCCESS;

	memset(&mbox_cmd, 0, sizeof(mbox_cmd));
	memset(&mbox_sts, 0, sizeof(mbox_sts));

	mbox_cmd[0] = MBOX_CMD_WRITE_FLASH;
	mbox_cmd[1] = LSDW(dma_addr);
	mbox_cmd[2] = MSDW(dma_addr);
	mbox_cmd[3] = offset;
	mbox_cmd[4] = length;
	mbox_cmd[5] = options;

	status = qla4xxx_mailbox_command(ha, 6, 2, &mbox_cmd[0], &mbox_sts[0]);
	if (status != QLA_SUCCESS) {
		DEBUG2(ql4_printk(KERN_WARNING, ha, "%s: MBOX_CMD_WRITE_FLASH "
				  "failed w/ status %04X, mbx1 %04X\n",
				  __func__, mbox_sts[0], mbox_sts[1]));
	}
	return status;
}
