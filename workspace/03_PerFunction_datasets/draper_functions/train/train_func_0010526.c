ath10k_swap_code_seg_init(struct ath10k *ar)
{
	int ret;
	struct ath10k_swap_code_seg_info *seg_info;

	if (!ar->swap.firmware_codeswap_len || !ar->swap.firmware_codeswap_data)
		return 0;

	seg_info = ath10k_swap_code_seg_alloc(ar,
					      ar->swap.firmware_codeswap_len);
	if (!seg_info) {
		ath10k_err(ar, "failed to allocate fw code swap segment\n");
		return -ENOMEM;
	}

	ret = ath10k_swap_code_seg_fill(ar, seg_info,
					ar->swap.firmware_codeswap_data,
					ar->swap.firmware_codeswap_len);

	if (ret) {
		ath10k_warn(ar, "failed to initialize fw code swap segment: %d\n",
			    ret);
		ath10k_swap_code_seg_free(ar, seg_info);
		return ret;
	}

	ar->swap.firmware_swap_code_seg_info = seg_info;

	return 0;
}
