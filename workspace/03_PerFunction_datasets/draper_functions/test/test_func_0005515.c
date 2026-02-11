qla82xx_write_disable_flash(struct qla_hw_data *ha)
{
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);
	qla82xx_wr_32(ha, QLA82XX_ROMUSB_ROM_INSTR_OPCODE, M25P_INSTR_WRDI);
	if (qla82xx_wait_rom_done(ha)) {
		ql_log(ql_log_warn, vha, 0xb00f,
		    "Error waiting for rom done.\n");
		return -1;
	}
	return 0;
}
