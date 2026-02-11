hga_clear_screen(void)
{
	unsigned char fillchar = 0xbf;
	unsigned long flags;

	spin_lock_irqsave(&hga_reg_lock, flags);
	if (hga_mode == HGA_TXT)
		fillchar = ' ';
	else if (hga_mode == HGA_GFX)
		fillchar = 0x00;
	spin_unlock_irqrestore(&hga_reg_lock, flags);
	if (fillchar != 0xbf)
		memset_io(hga_vram, fillchar, hga_vram_len);
}
