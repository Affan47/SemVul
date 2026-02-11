qla82xx_rom_lock(struct qla_hw_data *ha)
{
	int done = 0, timeout = 0;
	uint32_t lock_owner = 0;
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);

	while (!done) {

		done = qla82xx_rd_32(ha, QLA82XX_PCIE_REG(PCIE_SEM2_LOCK));
		if (done == 1)
			break;
		if (timeout >= qla82xx_rom_lock_timeout) {
			lock_owner = qla82xx_rd_32(ha, QLA82XX_ROM_LOCK_ID);
			ql_dbg(ql_dbg_p3p, vha, 0xb157,
			    "%s: Simultaneous flash access by following ports, active port = %d: accessing port = %d",
			    __func__, ha->portnum, lock_owner);
			return -1;
		}
		timeout++;
	}
	qla82xx_wr_32(ha, QLA82XX_ROM_LOCK_ID, ha->portnum);
	return 0;
}
