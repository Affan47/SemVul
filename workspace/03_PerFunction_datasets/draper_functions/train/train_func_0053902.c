qla82xx_protect_flash(struct qla_hw_data *ha)
{
	int ret;
	uint32_t val;
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);

	ret = ql82xx_rom_lock_d(ha);
	if (ret < 0) {
		ql_log(ql_log_warn, vha, 0xb016,
		    "ROM Lock failed.\n");
		return ret;
	}

	ret = qla82xx_read_status_reg(ha, &val);
	if (ret < 0)
		goto done_protect;

	val |= (BLOCK_PROTECT_BITS << 2);

	ret = qla82xx_write_status_reg(ha, val);
	if (ret < 0)
		ql_log(ql_log_warn, vha, 0xb017,
		    "Write status register failed.\n");

	if (qla82xx_write_disable_flash(ha) != 0)
		ql_log(ql_log_warn, vha, 0xb018,
		    "Write disable failed.\n");
done_protect:
	qla82xx_rom_unlock(ha);
	return ret;
}
