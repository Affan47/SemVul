f1x_map_sysaddr_to_csrow(struct mem_ctl_info *mci, u64 sys_addr,
				     struct err_info *err)
{
	struct amd64_pvt *pvt = mci->pvt_info;

	error_address_to_page_and_offset(sys_addr, err);

	err->csrow = f1x_translate_sysaddr_to_cs(pvt, sys_addr, &err->channel);
	if (err->csrow < 0) {
		err->err_code = ERR_CSROW;
		return;
	}


	if (dct_ganging_enabled(pvt))
		err->channel = get_channel_from_ecc_syndrome(mci, err->syndrome);
}
