shade_ximage_32(void *data, int bpl, int w, int h, int rm, int gm, int bm, int bg)
{
	SHADE_IMAGE(4, guint32, 0xff0000, 0xff00, 0xff);
}
