qla4_83xx_flash_lock(struct scsi_qla_host *ha)
{
	int lock_owner;
	int timeout = 0;
	uint32_t lock_status = 0;
	int ret_val = QLA_SUCCESS;

	while (lock_status == 0) {
		lock_status = qla4_83xx_rd_reg(ha, QLA83XX_FLASH_LOCK);
		if (lock_status)
			break;

		if (++timeout >= QLA83XX_FLASH_LOCK_TIMEOUT / 20) {
			lock_owner = qla4_83xx_rd_reg(ha,
						      QLA83XX_FLASH_LOCK_ID);
			ql4_printk(KERN_ERR, ha, "%s: flash lock by func %d failed, held by func %d\n",
				   __func__, ha->func_num, lock_owner);
			ret_val = QLA_ERROR;
			break;
		}
		msleep(20);
	}

	qla4_83xx_wr_reg(ha, QLA83XX_FLASH_LOCK_ID, ha->func_num);
	return ret_val;
}
