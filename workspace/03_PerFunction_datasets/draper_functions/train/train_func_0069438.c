ath6kl_fetch_fw_file(struct ath6kl *ar)
{
	char filename[100];
	int ret;

	if (ar->fw != NULL)
		return 0;


	if (WARN_ON(ar->hw.fw.fw == NULL))
		return -EINVAL;

	snprintf(filename, sizeof(filename), "%s/%s",
		 ar->hw.fw.dir, ar->hw.fw.fw);

	ret = ath6kl_get_fw(ar, filename, &ar->fw, &ar->fw_len);
	if (ret) {
		ath6kl_err("Failed to get firmware file %s: %d\n",
			   filename, ret);
		return ret;
	}

	return 0;
}
