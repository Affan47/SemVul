qla4xxx_set_acb(struct scsi_qla_host *ha, uint32_t *mbox_cmd,
		    uint32_t *mbox_sts, dma_addr_t acb_dma)
{
	int status = QLA_SUCCESS;

	memset(mbox_cmd, 0, sizeof(mbox_cmd[0]) * MBOX_REG_COUNT);
	memset(mbox_sts, 0, sizeof(mbox_sts[0]) * MBOX_REG_COUNT);
	mbox_cmd[0] = MBOX_CMD_SET_ACB;
	mbox_cmd[1] = 0;
	mbox_cmd[2] = LSDW(acb_dma);
	mbox_cmd[3] = MSDW(acb_dma);
	mbox_cmd[4] = sizeof(struct addr_ctrl_blk);

	status = qla4xxx_mailbox_command(ha, 5, 5, &mbox_cmd[0], &mbox_sts[0]);
	if (status != QLA_SUCCESS) {
		DEBUG2(ql4_printk(KERN_WARNING, ha,  "%s: MBOX_CMD_SET_ACB "
				  "failed w/ status %04X\n", __func__,
				  mbox_sts[0]));
	}
	return status;
}
