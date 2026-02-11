ath10k_bmi_execute(struct ath10k *ar, u32 address, u32 param, u32 *result)
{
	struct bmi_cmd cmd;
	union bmi_resp resp;
	u32 cmdlen = sizeof(cmd.id) + sizeof(cmd.execute);
	u32 resplen = sizeof(resp.execute);
	int ret;

	ath10k_dbg(ar, ATH10K_DBG_BMI, "bmi execute address 0x%x param 0x%x\n",
		   address, param);

	if (ar->bmi.done_sent) {
		ath10k_warn(ar, "command disallowed\n");
		return -EBUSY;
	}

	cmd.id            = __cpu_to_le32(BMI_EXECUTE);
	cmd.execute.addr  = __cpu_to_le32(address);
	cmd.execute.param = __cpu_to_le32(param);

	ret = ath10k_hif_exchange_bmi_msg(ar, &cmd, cmdlen, &resp, &resplen);
	if (ret) {
		ath10k_warn(ar, "unable to read from the device\n");
		return ret;
	}

	if (resplen < sizeof(resp.execute)) {
		ath10k_warn(ar, "invalid execute response length (%d)\n",
			    resplen);
		return -EIO;
	}

	*result = __le32_to_cpu(resp.execute.result);

	ath10k_dbg(ar, ATH10K_DBG_BMI, "bmi execute result 0x%x\n", *result);

	return 0;
}
