bnx2x_func_hw_init(struct bnx2x *bp,
			      struct bnx2x_func_state_params *params)
{
	u32 load_code = params->params.hw_init.load_phase;
	struct bnx2x_func_sp_obj *o = params->f_obj;
	const struct bnx2x_func_sp_drv_ops *drv = o->drv;
	int rc = 0;

	DP(BNX2X_MSG_SP, "function %d  load_code %x\n",
			 BP_ABS_FUNC(bp), load_code);


	rc = drv->gunzip_init(bp);
	if (rc)
		return rc;


	rc = drv->init_fw(bp);
	if (rc) {
		BNX2X_ERR("Error loading firmware\n");
		goto init_err;
	}


	switch (load_code) {
	case FW_MSG_CODE_DRV_LOAD_COMMON_CHIP:
		rc = bnx2x_func_init_cmn_chip(bp, drv);
		if (rc)
			goto init_err;

		break;
	case FW_MSG_CODE_DRV_LOAD_COMMON:
		rc = bnx2x_func_init_cmn(bp, drv);
		if (rc)
			goto init_err;

		break;
	case FW_MSG_CODE_DRV_LOAD_PORT:
		rc = bnx2x_func_init_port(bp, drv);
		if (rc)
			goto init_err;

		break;
	case FW_MSG_CODE_DRV_LOAD_FUNCTION:
		rc = bnx2x_func_init_func(bp, drv);
		if (rc)
			goto init_err;

		break;
	default:
		BNX2X_ERR("Unknown load_code (0x%x) from MCP\n", load_code);
		rc = -EINVAL;
	}

init_err:
	drv->gunzip_end(bp);


	if (!rc)
		o->complete_cmd(bp, o, BNX2X_F_CMD_HW_INIT);

	return rc;
}
