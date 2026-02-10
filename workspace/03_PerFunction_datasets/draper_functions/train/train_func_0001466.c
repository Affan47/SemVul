load_roms_init_memory()
{
	config_load_roms();
	memory_ptr_init();
	clk_setup_bram_version();
	if(g_rom_version >= 3) {
		g_c036_val_speed |= 0x40;
	} else {
		g_c036_val_speed &= (~0x40);
	}
	do_reset();


	set_memory16_c(0xe115fe, 0, 0);
}
