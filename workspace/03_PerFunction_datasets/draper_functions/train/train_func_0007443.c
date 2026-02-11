qla4_83xx_enable_mbox_intrs(struct scsi_qla_host *ha)
{
	uint32_t mb_int;

	if (!test_bit(AF_83XX_MBOX_INTR_ON, &ha->flags)) {
		mb_int = INT_ENABLE_FW_MB;
		writel(mb_int, &ha->qla4_83xx_reg->mbox_int);
		writel(0, &ha->qla4_83xx_reg->leg_int_mask);
		set_bit(AF_83XX_MBOX_INTR_ON, &ha->flags);
	}
}
