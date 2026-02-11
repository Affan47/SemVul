bnx2x_nic_load_request(struct bnx2x *bp, u32 *load_code)
{
	u32 param;


	bp->fw_seq =
		(SHMEM_RD(bp, func_mb[BP_FW_MB_IDX(bp)].drv_mb_header) &
		 DRV_MSG_SEQ_NUMBER_MASK);
	BNX2X_DEV_INFO("fw_seq 0x%08x\n", bp->fw_seq);


	bp->fw_drv_pulse_wr_seq =
		(SHMEM_RD(bp, func_mb[BP_FW_MB_IDX(bp)].drv_pulse_mb) &
		 DRV_PULSE_SEQ_MASK);
	BNX2X_DEV_INFO("drv_pulse 0x%x\n", bp->fw_drv_pulse_wr_seq);

	param = DRV_MSG_CODE_LOAD_REQ_WITH_LFA;

	if (IS_MF_SD(bp) && bnx2x_port_after_undi(bp))
		param |= DRV_MSG_CODE_LOAD_REQ_FORCE_LFA;


	(*load_code) = bnx2x_fw_command(bp, DRV_MSG_CODE_LOAD_REQ, param);


	if (!(*load_code)) {
		BNX2X_ERR("MCP response failure, aborting\n");
		return -EBUSY;
	}


	if ((*load_code) == FW_MSG_CODE_DRV_LOAD_REFUSED) {
		BNX2X_ERR("MCP refused load request, aborting\n");
		return -EBUSY;
	}
	return 0;
}
