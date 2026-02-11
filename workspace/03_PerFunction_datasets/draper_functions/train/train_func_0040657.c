qla4xxx_set_ddb_entry(struct scsi_qla_host * ha, uint16_t fw_ddb_index,
			  dma_addr_t fw_ddb_entry_dma, uint32_t *mbx_sts)
{
	uint32_t mbox_cmd[MBOX_REG_COUNT];
	uint32_t mbox_sts[MBOX_REG_COUNT];
	int status;


	memset(&mbox_cmd, 0, sizeof(mbox_cmd));
	memset(&mbox_sts, 0, sizeof(mbox_sts));

	mbox_cmd[0] = MBOX_CMD_SET_DATABASE_ENTRY;
	mbox_cmd[1] = (uint32_t) fw_ddb_index;
	mbox_cmd[2] = LSDW(fw_ddb_entry_dma);
	mbox_cmd[3] = MSDW(fw_ddb_entry_dma);
	mbox_cmd[4] = sizeof(struct dev_db_entry);

	status = qla4xxx_mailbox_command(ha, MBOX_REG_COUNT, 5, &mbox_cmd[0],
					 &mbox_sts[0]);
	if (mbx_sts)
		*mbx_sts = mbox_sts[0];
	DEBUG2(printk("scsi%ld: %s: status=%d mbx0=0x%x mbx4=0x%x\n",
	    ha->host_no, __func__, status, mbox_sts[0], mbox_sts[4]);)

	return status;
}
