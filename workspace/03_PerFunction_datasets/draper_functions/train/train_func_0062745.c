ath6kl_fetch_board_file(struct ath6kl *ar)
{
	const char *filename;
	int ret;

	if (ar->fw_board != NULL)
		return 0;

	if (WARN_ON(ar->hw.fw_board == NULL))
		return -EINVAL;

	filename = ar->hw.fw_board;

	ret = ath6kl_get_fw(ar, filename, &ar->fw_board,
			    &ar->fw_board_len);
	if (ret == 0) {

		return 0;
	}

	if (check_device_tree(ar)) {

		return 0;
	}


	ath6kl_warn("Failed to get board file %s (%d), trying to find default board file.\n",
		    filename, ret);

	filename = ar->hw.fw_default_board;

	ret = ath6kl_get_fw(ar, filename, &ar->fw_board,
			    &ar->fw_board_len);
	if (ret) {
		ath6kl_err("Failed to get default board file %s: %d\n",
			   filename, ret);
		return ret;
	}

	ath6kl_warn("WARNING! No proper board file was not found, instead using a default board file.\n");
	ath6kl_warn("Most likely your hardware won't work as specified. Install correct board file!\n");

	return 0;
}
