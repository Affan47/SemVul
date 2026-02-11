hga_blank(int blank_mode)
{
	unsigned long flags;

	spin_lock_irqsave(&hga_reg_lock, flags);
	if (blank_mode) {
		outb_p(0x00, HGA_MODE_PORT);
	} else {
		outb_p(HGA_MODE_VIDEO_EN | HGA_MODE_GRAPHICS, HGA_MODE_PORT);
	}
	spin_unlock_irqrestore(&hga_reg_lock, flags);
}
