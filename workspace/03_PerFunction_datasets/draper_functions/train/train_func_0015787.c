qla2x00_verify_checksum(scsi_qla_host_t *vha, uint32_t risc_addr)
{
	int rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1035,
	    "Entered %s.\n", __func__);

	mcp->mb[0] = MBC_VERIFY_CHECKSUM;
	mcp->out_mb = MBX_0;
	mcp->in_mb = MBX_0;
	if (IS_FWI2_CAPABLE(vha->hw)) {
		mcp->mb[1] = MSW(risc_addr);
		mcp->mb[2] = LSW(risc_addr);
		mcp->out_mb |= MBX_2|MBX_1;
		mcp->in_mb |= MBX_2|MBX_1;
	} else {
		mcp->mb[1] = LSW(risc_addr);
		mcp->out_mb |= MBX_1;
		mcp->in_mb |= MBX_1;
	}

	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	if (rval != QLA_SUCCESS) {
		ql_dbg(ql_dbg_mbx, vha, 0x1036,
		    "Failed=%x chm sum=%x.\n", rval, IS_FWI2_CAPABLE(vha->hw) ?
		    (mcp->mb[2] << 16) | mcp->mb[1] : mcp->mb[1]);
	} else {
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1037,
		    "Done %s.\n", __func__);
	}

	return rval;
}
