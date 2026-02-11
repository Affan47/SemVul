dcs2_init(offs_t polling_offset)
{
	UINT8 *romsrc;
	int page, i;


	dcs_cpunum = mame_find_cpu_index("dcs2");


	dcs_sram_bank1 = (UINT16 *)(memory_region(REGION_CPU1 + dcs_cpunum) + 0x8000);


	romsrc = memory_region(REGION_CPU1 + dcs_cpunum) + ADSP2100_SIZE;
	dcs_expanded_rom = (UINT16 *)(memory_region(REGION_CPU1 + dcs_cpunum) + 0xc000);
	for (page = 0; page < 8; page++)
		for (i = 0; i < 0x400; i++)
			dcs_expanded_rom[0x400 * page + i] = romsrc[BYTE_XOR_LE(0x1000 * page + i)];


	dcs.reg_timer = timer_alloc(dcs_irq);
	dcs.sport_timer = timer_alloc(sport0_irq);


	dcs.auto_ack = 0;
	dcs.output_full_cb = NULL;
	dcs.input_empty_cb = NULL;
	dcs.fifo_data_r = NULL;
	dcs.fifo_status_r = NULL;


	if (polling_offset)
		dcs_polling_base = install_mem_read16_handler(dcs_cpunum, ADSP_DATA_ADDR_RANGE(polling_offset, polling_offset), dcs_polling_r);


	dcs_reset();
}
