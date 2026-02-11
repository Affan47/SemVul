ath10k_core_parse_bd_ie_board(struct ath10k *ar,
					 const void *buf, size_t buf_len,
					 const char *boardname)
{
	const struct ath10k_fw_ie *hdr;
	bool name_match_found;
	int ret, board_ie_id;
	size_t board_ie_len;
	const void *board_ie_data;

	name_match_found = false;


	while (buf_len > sizeof(struct ath10k_fw_ie)) {
		hdr = buf;
		board_ie_id = le32_to_cpu(hdr->id);
		board_ie_len = le32_to_cpu(hdr->len);
		board_ie_data = hdr->data;

		buf_len -= sizeof(*hdr);
		buf += sizeof(*hdr);

		if (buf_len < ALIGN(board_ie_len, 4)) {
			ath10k_err(ar, "invalid ATH10K_BD_IE_BOARD length: %zu < %zu\n",
				   buf_len, ALIGN(board_ie_len, 4));
			ret = -EINVAL;
			goto out;
		}

		switch (board_ie_id) {
		case ATH10K_BD_IE_BOARD_NAME:
			ath10k_dbg_dump(ar, ATH10K_DBG_BOOT, "board name", "",
					board_ie_data, board_ie_len);

			if (board_ie_len != strlen(boardname))
				break;

			ret = memcmp(board_ie_data, boardname, strlen(boardname));
			if (ret)
				break;

			name_match_found = true;
			ath10k_dbg(ar, ATH10K_DBG_BOOT,
				   "boot found match for name '%s'",
				   boardname);
			break;
		case ATH10K_BD_IE_BOARD_DATA:
			if (!name_match_found)

				break;

			ath10k_dbg(ar, ATH10K_DBG_BOOT,
				   "boot found board data for '%s'",
				   boardname);

			ar->board_data = board_ie_data;
			ar->board_len = board_ie_len;

			ret = 0;
			goto out;
		default:
			ath10k_warn(ar, "unknown ATH10K_BD_IE_BOARD found: %d\n",
				    board_ie_id);
			break;
		}


		board_ie_len = ALIGN(board_ie_len, 4);

		buf_len -= board_ie_len;
		buf += board_ie_len;
	}


	ret = -ENOENT;

out:
	return ret;
}
