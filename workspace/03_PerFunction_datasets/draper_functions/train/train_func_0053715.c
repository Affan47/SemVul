qla4_8xxx_update_idc_reg(struct scsi_qla_host *ha)
{
	uint32_t drv_active;
	int rval = QLA_SUCCESS;

	if (test_bit(AF_INIT_DONE, &ha->flags))
		goto exit_update_idc_reg;

	ha->isp_ops->idc_lock(ha);
	qla4_8xxx_set_drv_active(ha);


	if (is_qla8032(ha) || is_qla8042(ha)) {
		drv_active = qla4_8xxx_rd_direct(ha, QLA8XXX_CRB_DRV_ACTIVE);
		if ((drv_active == (1 << ha->func_num)) && !ql4xdontresethba)
			qla4_83xx_clear_idc_dontreset(ha);
	}

	if (is_qla8022(ha)) {
		qla4_82xx_set_idc_ver(ha);
	} else if (is_qla8032(ha) || is_qla8042(ha)) {
		rval = qla4_83xx_set_idc_ver(ha);
		if (rval == QLA_ERROR)
			qla4_8xxx_clear_drv_active(ha);
	}

	ha->isp_ops->idc_unlock(ha);

exit_update_idc_reg:
	return rval;
}
