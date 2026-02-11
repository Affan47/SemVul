init_crusnwld_common(offs_t speedup)
{
	dcs_init();
	adc_shift = 16;


	install_mem_write32_handler(0, ADDR_RANGE(0x994000, 0x994000), crusnwld_control_w);


	midway_serial_pic_init(450);
	install_mem_read32_handler(0, ADDR_RANGE(0x991030, 0x991030), offroadc_serial_status_r);
	install_mem_read32_handler(0, ADDR_RANGE(0x996000, 0x996000), offroadc_serial_data_r);
	install_mem_write32_handler(0, ADDR_RANGE(0x996000, 0x996000), offroadc_serial_data_w);


	install_mem_read32_handler(0, ADDR_RANGE(0x9d0000, 0x9d1fff), bit_data_r);
	install_mem_write32_handler(0, ADDR_RANGE(0x9d0000, 0x9d0000), bit_reset_w);


	if (speedup)
		generic_speedup = install_mem_read32_handler(0, ADDR_RANGE(speedup, speedup + 1), generic_speedup_r);
}
