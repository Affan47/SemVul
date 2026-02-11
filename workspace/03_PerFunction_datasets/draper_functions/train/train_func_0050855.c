init_ds3(void)
{

	install_mem_read16_handler(hdcpu_main, 0x800000, 0x807fff, hd68k_ds3_program_r);
	install_mem_write16_handler(hdcpu_main, 0x800000, 0x807fff, hd68k_ds3_program_w);


	install_mem_read16_handler(hdcpu_main, 0x808000, 0x80bfff, hd68k_adsp_data_r);
	install_mem_write16_handler(hdcpu_main, 0x808000, 0x80bfff, hd68k_adsp_data_w);
	install_mem_read16_handler(hdcpu_main, 0x80c000, 0x80dfff, hdds3_special_r);
	install_mem_write16_handler(hdcpu_main, 0x80c000, 0x80dfff, hdds3_special_w);


	install_mem_read16_handler(hdcpu_main, 0x820000, 0x8207ff, hd68k_ds3_gdata_r);
	install_mem_read16_handler(hdcpu_main, 0x820800, 0x820fff, hd68k_ds3_girq_state_r);
	install_mem_write16_handler(hdcpu_main, 0x820000, 0x8207ff, hd68k_ds3_gdata_w);
	install_mem_write16_handler(hdcpu_main, 0x821000, 0x8217ff, hd68k_adsp_irq_clear_w);
	install_mem_read16_handler(hdcpu_main, 0x822000, 0x8227ff, hd68k_ds3_sdata_r);
	install_mem_read16_handler(hdcpu_main, 0x822800, 0x822fff, hd68k_ds3_sirq_state_r);
	install_mem_write16_handler(hdcpu_main, 0x822000, 0x8227ff, hd68k_ds3_sdata_w);
	install_mem_write16_handler(hdcpu_main, 0x823800, 0x823fff, hd68k_ds3_control_w);


	if (hdcpu_sound != -1 && Machine->drv->cpu[hdcpu_sound].cpu_type == CPU_ADSP2105)
		adsp2105_load_boot_data((data8_t *)(memory_region(REGION_CPU1 + hdcpu_sound) + ADSP2100_SIZE),
								(data32_t *)(memory_region(REGION_CPU1 + hdcpu_sound) + ADSP2100_PGM_OFFSET));
	if (hdcpu_sounddsp != -1 && Machine->drv->cpu[hdcpu_sounddsp].cpu_type == CPU_ADSP2105)
		adsp2105_load_boot_data((data8_t *)(memory_region(REGION_CPU1 + hdcpu_sounddsp) + ADSP2100_SIZE),
								(data32_t *)(memory_region(REGION_CPU1 + hdcpu_sounddsp) + ADSP2100_PGM_OFFSET));


}
