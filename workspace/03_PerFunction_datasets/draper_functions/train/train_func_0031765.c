qlafx00_get_firmware_state(scsi_qla_host_t *vha, uint32_t *states)
{
	int rval;
	struct mbx_cmd_32 mc;
	struct mbx_cmd_32 *mcp = &mc;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1169,
	    "Entered %s.\n", __func__);

	mcp->mb[0] = MBC_GET_FIRMWARE_STATE;
	mcp->out_mb = MBX_0;
	mcp->in_mb = MBX_1|MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qlafx00_mailbox_command(vha, mcp);


	states[0] = mcp->mb[1];

	if (rval != QLA_SUCCESS) {
		ql_dbg(ql_dbg_mbx, vha, 0x116a,
		    "Failed=%x mb[0]=%x.\n", rval, mcp->mb[0]);
	} else {
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x116b,
		    "Done %s.\n", __func__);
	}
	return rval;
}
