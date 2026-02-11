denali_nand_timing_set(struct denali_nand_info *denali)
{
	uint16_t status = PASS;
	uint32_t id_bytes[8], addr;
	uint8_t maf_id, device_id;
	int i;

	dev_dbg(denali->dev, "%s, Line %d, Function: %s\n",
			__FILE__, __LINE__, __func__);


	addr = MODE_11 | BANK(denali->flash_bank);
	index_addr(denali, addr | 0, 0x90);
	index_addr(denali, addr | 1, 0);
	for (i = 0; i < 8; i++)
		index_addr_read_data(denali, addr | 2, &id_bytes[i]);
	maf_id = id_bytes[0];
	device_id = id_bytes[1];

	if (ioread32(denali->flash_reg + ONFI_DEVICE_NO_OF_LUNS) &
		ONFI_DEVICE_NO_OF_LUNS__ONFI_DEVICE) {
		if (FAIL == get_onfi_nand_para(denali))
			return FAIL;
	} else if (maf_id == 0xEC) {
		get_samsung_nand_para(denali, device_id);
	} else if (maf_id == 0x98) {
		get_toshiba_nand_para(denali);
	} else if (maf_id == 0xAD) {
		get_hynix_nand_para(denali, device_id);
	}

	dev_info(denali->dev,
			"Dump timing register values:\n"
			"acc_clks: %d, re_2_we: %d, re_2_re: %d\n"
			"we_2_re: %d, addr_2_data: %d, rdwr_en_lo_cnt: %d\n"
			"rdwr_en_hi_cnt: %d, cs_setup_cnt: %d\n",
			ioread32(denali->flash_reg + ACC_CLKS),
			ioread32(denali->flash_reg + RE_2_WE),
			ioread32(denali->flash_reg + RE_2_RE),
			ioread32(denali->flash_reg + WE_2_RE),
			ioread32(denali->flash_reg + ADDR_2_DATA),
			ioread32(denali->flash_reg + RDWR_EN_LO_CNT),
			ioread32(denali->flash_reg + RDWR_EN_HI_CNT),
			ioread32(denali->flash_reg + CS_SETUP_CNT));

	find_valid_banks(denali);

	detect_partition_feature(denali);


	if (onfi_timing_mode != NAND_DEFAULT_TIMINGS)
		nand_onfi_timing_set(denali, onfi_timing_mode);

	return status;
}
