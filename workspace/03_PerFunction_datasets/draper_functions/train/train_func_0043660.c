sh_vou_hw_init(struct sh_vou_device *vou_dev)
{
	struct sh_vou_pdata *pdata = vou_dev->pdata;
	u32 voucr = sh_vou_ntsc_mode(pdata->bus_fmt) << 29;
	int i = 100;


	sh_vou_reg_a_write(vou_dev, VOUIR, 0);


	sh_vou_reg_a_write(vou_dev, VOUSRR, 0x101);
	while (--i && (sh_vou_reg_a_read(vou_dev, VOUSRR) & 0x101))
		udelay(1);

	if (!i)
		return -ETIMEDOUT;

	dev_dbg(vou_dev->v4l2_dev.dev, "Reset took %dus\n", 100 - i);

	if (pdata->flags & SH_VOU_PCLK_FALLING)
		voucr |= 1 << 28;
	if (pdata->flags & SH_VOU_HSYNC_LOW)
		voucr |= 1 << 27;
	if (pdata->flags & SH_VOU_VSYNC_LOW)
		voucr |= 1 << 26;
	sh_vou_reg_ab_set(vou_dev, VOUCR, voucr, 0xfc000000);


	sh_vou_reg_a_write(vou_dev, VOURCR, 4);

	sh_vou_reg_ab_write(vou_dev, VOUMSR, 0x800000);

	sh_vou_set_fmt_vid_out(vou_dev, &vou_dev->pix);

	return 0;
}
