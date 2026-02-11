__qla83xx_set_drv_presence(scsi_qla_host_t *vha)
{
	int rval = QLA_SUCCESS;
	struct qla_hw_data *ha = vha->hw;
	uint32_t drv_presence;

	rval = qla83xx_rd_reg(vha, QLA83XX_IDC_DRV_PRESENCE, &drv_presence);
	if (rval == QLA_SUCCESS) {
		drv_presence |= (1 << ha->portnum);
		rval = qla83xx_wr_reg(vha, QLA83XX_IDC_DRV_PRESENCE,
		    drv_presence);
	}

	return rval;
}
