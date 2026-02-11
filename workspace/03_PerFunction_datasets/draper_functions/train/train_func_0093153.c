qla2x00_iidma_fcport(scsi_qla_host_t *vha, fc_port_t *fcport)
{
	int rval;
	uint16_t mb[MAILBOX_REGISTER_COUNT];
	struct qla_hw_data *ha = vha->hw;

	if (!IS_IIDMA_CAPABLE(ha))
		return;

	if (atomic_read(&fcport->state) != FCS_ONLINE)
		return;

	if (fcport->fp_speed == PORT_SPEED_UNKNOWN ||
	    fcport->fp_speed > ha->link_data_rate)
		return;

	rval = qla2x00_set_idma_speed(vha, fcport->loop_id, fcport->fp_speed,
	    mb);
	if (rval != QLA_SUCCESS) {
		ql_dbg(ql_dbg_disc, vha, 0x2004,
		    "Unable to adjust iIDMA %8phN -- %04x %x %04x %04x.\n",
		    fcport->port_name, rval, fcport->fp_speed, mb[0], mb[1]);
	} else {
		ql_dbg(ql_dbg_disc, vha, 0x2005,
		    "iIDMA adjusted to %s GB/s on %8phN.\n",
		    qla2x00_get_link_speed_str(ha, fcport->fp_speed),
		    fcport->port_name);
	}
}
