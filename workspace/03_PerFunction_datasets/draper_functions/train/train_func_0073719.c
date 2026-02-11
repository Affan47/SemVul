qla2x00_get_xgmac_stats(scsi_qla_host_t *vha, dma_addr_t stats_dma,
    uint16_t size_in_bytes, uint16_t *actual_size)
{
	int rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10ee,
	    "Entered %s.\n", __func__);

	if (!IS_CNA_CAPABLE(vha->hw))
		return QLA_FUNCTION_FAILED;

	mcp->mb[0] = MBC_GET_XGMAC_STATS;
	mcp->mb[2] = MSW(stats_dma);
	mcp->mb[3] = LSW(stats_dma);
	mcp->mb[6] = MSW(MSD(stats_dma));
	mcp->mb[7] = LSW(MSD(stats_dma));
	mcp->mb[8] = size_in_bytes >> 2;
	mcp->out_mb = MBX_8|MBX_7|MBX_6|MBX_3|MBX_2|MBX_0;
	mcp->in_mb = MBX_2|MBX_1|MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	if (rval != QLA_SUCCESS) {
		ql_dbg(ql_dbg_mbx, vha, 0x10ef,
		    "Failed=%x mb[0]=%x mb[1]=%x mb[2]=%x.\n",
		    rval, mcp->mb[0], mcp->mb[1], mcp->mb[2]);
	} else {
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10f0,
		    "Done %s.\n", __func__);


		*actual_size = mcp->mb[2] << 2;
	}

	return rval;
}
