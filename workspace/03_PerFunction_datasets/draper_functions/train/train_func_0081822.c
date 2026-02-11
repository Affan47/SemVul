qla2x00_write_sfp(scsi_qla_host_t *vha, dma_addr_t sfp_dma, uint8_t *sfp,
	uint16_t dev, uint16_t off, uint16_t len, uint16_t opt)
{
	int rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;
	struct qla_hw_data *ha = vha->hw;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10eb,
	    "Entered %s.\n", __func__);

	if (!IS_FWI2_CAPABLE(ha))
		return QLA_FUNCTION_FAILED;

	if (len == 1)
		opt |= BIT_0;

	if (opt & BIT_0)
		len = *sfp;

	mcp->mb[0] = MBC_WRITE_SFP;
	mcp->mb[1] = dev;
	mcp->mb[2] = MSW(sfp_dma);
	mcp->mb[3] = LSW(sfp_dma);
	mcp->mb[6] = MSW(MSD(sfp_dma));
	mcp->mb[7] = LSW(MSD(sfp_dma));
	mcp->mb[8] = len;
	mcp->mb[9] = off;
	mcp->mb[10] = opt;
	mcp->out_mb = MBX_10|MBX_9|MBX_8|MBX_7|MBX_6|MBX_3|MBX_2|MBX_1|MBX_0;
	mcp->in_mb = MBX_1|MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	if (rval != QLA_SUCCESS) {
		ql_dbg(ql_dbg_mbx, vha, 0x10ec,
		    "Failed=%x mb[0]=%x.\n", rval, mcp->mb[0]);
	} else {
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10ed,
		    "Done %s.\n", __func__);
	}

	return rval;
}
