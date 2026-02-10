qla2x00_write_serdes_word(scsi_qla_host_t *vha, uint16_t addr, uint16_t data)
{
	int rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	if (!IS_QLA25XX(vha->hw) && !IS_QLA2031(vha->hw) &&
	    !IS_QLA27XX(vha->hw))
		return QLA_FUNCTION_FAILED;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1182,
	    "Entered %s.\n", __func__);

	mcp->mb[0] = MBC_WRITE_SERDES;
	mcp->mb[1] = addr;
	if (IS_QLA2031(vha->hw))
		mcp->mb[2] = data & 0xff;
	else
		mcp->mb[2] = data;

	mcp->mb[3] = 0;
	mcp->out_mb = MBX_3|MBX_2|MBX_1|MBX_0;
	mcp->in_mb = MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	if (rval != QLA_SUCCESS) {
		ql_dbg(ql_dbg_mbx, vha, 0x1183,
		    "Failed=%x mb[0]=%x.\n", rval, mcp->mb[0]);
	} else {
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1184,
		    "Done %s.\n", __func__);
	}

	return rval;
}
