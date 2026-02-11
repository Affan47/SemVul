qat_hal_init_rd_xfer(struct icp_qat_fw_loader_handle *handle,
			 unsigned char ae, unsigned char ctx_mask,
			 enum icp_qat_uof_regtype reg_type,
			 unsigned short reg_num, unsigned int regdata)
{
	int stat = 0;
	unsigned short reg;
	unsigned char ctx = 0;
	enum icp_qat_uof_regtype type;

	if (reg_num >= ICP_QAT_UCLO_MAX_XFER_REG)
		return -EINVAL;

	do {
		if (ctx_mask == 0) {
			qat_hal_convert_abs_to_rel(handle, ae, reg_num, &reg,
						   &ctx);
			type = reg_type - 3;
		} else {
			reg = reg_num;
			type = reg_type;
			if (!test_bit(ctx, (unsigned long *)&ctx_mask))
				continue;
		}
		stat = qat_hal_put_rel_rd_xfer(handle, ae, ctx, type, reg,
					       regdata);
		if (stat) {
			pr_err("QAT: write rd xfer fail\n");
			return -EINVAL;
		}
	} while (ctx_mask && (ctx++ < ICP_QAT_UCLO_MAX_CTX));

	return 0;
}
