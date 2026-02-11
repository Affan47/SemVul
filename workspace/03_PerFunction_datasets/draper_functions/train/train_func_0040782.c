OSDSetColor(struct av7110 *av7110, u8 color, u8 r, u8 g, u8 b, u8 blend)
{
	int ret;

	u16 ch, cl;
	u32 yuv;

	yuv = blend ? RGB2YUV(r,g,b) : 0;
	cl = (yuv & 0xffff);
	ch = ((yuv >> 16) & 0xffff);
	ret = SetColor_(av7110, av7110->osdwin, bpp2pal[av7110->osdbpp[av7110->osdwin]],
			color, ch, cl);
	if (!ret)
		ret = SetBlend_(av7110, av7110->osdwin, bpp2pal[av7110->osdbpp[av7110->osdwin]],
				color, ((blend >> 4) & 0x0f));
	return ret;
}
