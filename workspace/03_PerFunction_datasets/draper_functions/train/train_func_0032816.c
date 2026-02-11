qla2x00_execute_fw(scsi_qla_host_t *vha, uint32_t risc_addr)
{
	int rval;
	struct qla_hw_data *ha = vha->hw;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1025,
	    "Entered %s.\n", __func__);

	mcp->mb[0] = MBC_EXECUTE_FIRMWARE;
	mcp->out_mb = MBX_0;
	mcp->in_mb = MBX_0;
	if (IS_FWI2_CAPABLE(ha)) {
		mcp->mb[1] = MSW(risc_addr);
		mcp->mb[2] = LSW(risc_addr);
		mcp->mb[3] = 0;
		if (IS_QLA25XX(ha) || IS_QLA81XX(ha) || IS_QLA83XX(ha) ||
		    IS_QLA27XX(ha)) {
			struct nvram_81xx *nv = ha->nvram;
			mcp->mb[4] = (nv->enhanced_features &
			    EXTENDED_BB_CREDITS);
		} else
			mcp->mb[4] = 0;

		if (ha->flags.exlogins_enabled)
			mcp->mb[4] |= ENABLE_EXTENDED_LOGIN;

		if (ha->flags.exchoffld_enabled)
			mcp->mb[4] |= ENABLE_EXCHANGE_OFFLD;

		mcp->out_mb |= MBX_4|MBX_3|MBX_2|MBX_1;
		mcp->in_mb |= MBX_1;
	} else {
		mcp->mb[1] = LSW(risc_addr);
		mcp->out_mb |= MBX_1;
		if (IS_QLA2322(ha) || IS_QLA6322(ha)) {
			mcp->mb[2] = 0;
			mcp->out_mb |= MBX_2;
		}
	}

	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	if (rval != QLA_SUCCESS) {
		ql_dbg(ql_dbg_mbx, vha, 0x1026,
		    "Failed=%x mb[0]=%x.\n", rval, mcp->mb[0]);
	} else {
		if (IS_FWI2_CAPABLE(ha)) {
			ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1027,
			    "Done exchanges=%x.\n", mcp->mb[1]);
		} else {
			ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1028,
			    "Done %s.\n", __func__);
		}
	}

	return rval;
}
