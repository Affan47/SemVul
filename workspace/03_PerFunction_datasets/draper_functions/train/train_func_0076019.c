s3fb_ddc_write(struct s3fb_info *par, u8 val)
{
	if (s3fb_ddc_needs_mmio(par->chip))
		writeb(val, par->mmio + DDC_MMIO_REG);
	else
		vga_wcrt(par->state.vgabase, DDC_REG, val);
}
