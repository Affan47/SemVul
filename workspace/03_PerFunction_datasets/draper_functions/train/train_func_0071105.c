t4vf_query_params(struct adapter *adapter, unsigned int nparams,
			     const u32 *params, u32 *vals)
{
	int i, ret;
	struct fw_params_cmd cmd, rpl;
	struct fw_params_param *p;
	size_t len16;

	if (nparams > 7)
		return -EINVAL;

	memset(&cmd, 0, sizeof(cmd));
	cmd.op_to_vfn = cpu_to_be32(FW_CMD_OP_V(FW_PARAMS_CMD) |
				    FW_CMD_REQUEST_F |
				    FW_CMD_READ_F);
	len16 = DIV_ROUND_UP(offsetof(struct fw_params_cmd,
				      param[nparams].mnem), 16);
	cmd.retval_len16 = cpu_to_be32(FW_CMD_LEN16_V(len16));
	for (i = 0, p = &cmd.param[0]; i < nparams; i++, p++)
		p->mnem = htonl(*params++);

	ret = t4vf_wr_mbox(adapter, &cmd, sizeof(cmd), &rpl);
	if (ret == 0)
		for (i = 0, p = &rpl.param[0]; i < nparams; i++, p++)
			*vals++ = be32_to_cpu(p->val);
	return ret;
}
