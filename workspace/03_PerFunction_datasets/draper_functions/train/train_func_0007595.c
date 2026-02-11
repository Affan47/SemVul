qla82xx_wait_rom_busy(struct qla_hw_data *ha)
{
	long timeout = 0;
	long done = 0 ;
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);

	while (done == 0) {
		done = qla82xx_rd_32(ha, QLA82XX_ROMUSB_GLB_STATUS);
		done &= 4;
		timeout++;
		if (timeout >= rom_max_timeout) {
			ql_dbg(ql_dbg_p3p, vha, 0xb00a,
			    "%s: Timeout reached waiting for rom busy.\n",
			    QLA2XXX_DRIVER_NAME);
			return -1;
		}
	}
	return 0;
}
