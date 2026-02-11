qla4_8xxx_get_flash_info(struct scsi_qla_host *ha)
{
	int ret;
	uint32_t flt_addr;

	ret = qla4_8xxx_find_flt_start(ha, &flt_addr);
	if (ret != QLA_SUCCESS)
		return ret;

	qla4_8xxx_get_flt_info(ha, flt_addr);
	if (is_qla8022(ha)) {
		qla4_82xx_get_fdt_info(ha);
		qla4_82xx_get_idc_param(ha);
	} else if (is_qla8032(ha) || is_qla8042(ha)) {
		qla4_83xx_get_idc_param(ha);
	}

	return QLA_SUCCESS;
}
