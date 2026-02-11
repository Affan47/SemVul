qla82xx_load_risc(scsi_qla_host_t *vha, uint32_t *srisc_addr)
{
	int rval = -1;
	struct qla_hw_data *ha = vha->hw;

	if (IS_QLA82XX(ha))
		rval = qla82xx_device_state_handler(vha);
	else if (IS_QLA8044(ha)) {
		qla8044_idc_lock(ha);

		qla83xx_reset_ownership(vha);
		qla8044_idc_unlock(ha);
		rval = qla8044_device_state_handler(vha);
	}
	return rval;
}
