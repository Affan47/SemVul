qla82xx_set_drv_active(scsi_qla_host_t *vha)
{
	uint32_t drv_active;
	struct qla_hw_data *ha = vha->hw;

	drv_active = qla82xx_rd_32(ha, QLA82XX_CRB_DRV_ACTIVE);


	if (drv_active == 0xffffffff) {
		qla82xx_wr_32(ha, QLA82XX_CRB_DRV_ACTIVE,
			QLA82XX_DRV_NOT_ACTIVE);
		drv_active = qla82xx_rd_32(ha, QLA82XX_CRB_DRV_ACTIVE);
	}
	drv_active |= (QLA82XX_DRV_ACTIVE << (ha->portnum * 4));
	qla82xx_wr_32(ha, QLA82XX_CRB_DRV_ACTIVE, drv_active);
}
