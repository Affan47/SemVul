segae_vdp_start( UINT8 chip )
{
	UINT8 temp;


	segae_vdp_vram[chip] = auto_malloc(0x8000);
	segae_vdp_vrambank[chip] = 0;


	segae_vdp_cram[chip] = auto_malloc(0x20);


	segae_vdp_regs[chip] = auto_malloc(0x20);


	if (!segae_vdp_vram[chip] || !segae_vdp_cram[chip] || !segae_vdp_regs[chip])
		return 1;


	memset(segae_vdp_vram[chip], 0, 0x8000);
	memset(segae_vdp_cram[chip], 0, 0x20);
	memset(segae_vdp_regs[chip], 0, 0x20);


	segae_vdp_accessaddr[chip] = 0;
	segae_vdp_accessmode[chip] = 0;
	segae_vdp_cmdpart[chip] = 0;
	segae_vdp_command[chip] = 0;


	for (temp=0;temp<32;temp++)
		palette_set_color(temp + 32*chip+segasyse_palettebase, 0, 0, 0);


	{
		char buf[20];
			sprintf(buf,"SEGASYSE-VDP-%01x",chip);
			state_save_register_UINT8 ( buf, 0, "Video RAM",		segae_vdp_vram[chip], 0x8000);
			state_save_register_UINT8 ( buf, 0, "Colour RAM",		segae_vdp_cram[chip], 0x20);
			state_save_register_UINT8 ( buf, 0, "Registers",		segae_vdp_regs[chip], 0x20);
			state_save_register_UINT8 ( buf, 0, "Command Part",		&segae_vdp_cmdpart[chip], 1);
			state_save_register_UINT16( buf, 0, "Command Word",		&segae_vdp_command[chip], 1);
			state_save_register_UINT8 ( buf, 0, "Access Mode",		&segae_vdp_accessmode[chip], 1);
			state_save_register_UINT16( buf, 0, "Access Address",	&segae_vdp_accessaddr[chip], 1);
			state_save_register_UINT8 ( buf, 0, "VRAM Bank",		&segae_vdp_vrambank[chip], 1);
	}


	return 0;
}
