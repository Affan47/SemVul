ath10k_bmi_lz_data(struct ath10k *ar, const void *buffer, u32 length)
{
	struct bmi_cmd cmd;
	u32 hdrlen = sizeof(cmd.id) + sizeof(cmd.lz_data);
	u32 txlen;
	int ret;

	ath10k_dbg(ar, ATH10K_DBG_BMI, "bmi lz data buffer 0x%p length %d\n",
		   buffer, length);

	if (ar->bmi.done_sent) {
		ath10k_warn(ar, "command disallowed\n");
		return -EBUSY;
	}

	while (length) {
		txlen = min(length, BMI_MAX_DATA_SIZE - hdrlen);

		WARN_ON_ONCE(txlen & 3);

		cmd.id          = __cpu_to_le32(BMI_LZ_DATA);
		cmd.lz_data.len = __cpu_to_le32(txlen);
		memcpy(cmd.lz_data.payload, buffer, txlen);

		ret = ath10k_hif_exchange_bmi_msg(ar, &cmd, hdrlen + txlen,
						  NULL, NULL);
		if (ret) {
			ath10k_warn(ar, "unable to write to the device\n");
			return ret;
		}

		buffer += txlen;
		length -= txlen;
	}

	return 0;
}
