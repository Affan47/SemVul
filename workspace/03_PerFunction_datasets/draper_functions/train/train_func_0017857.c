orbit_draw_sprites(struct mame_bitmap* bitmap, const struct rectangle* cliprect)
{
	const UINT8* p = orbit_sprite_ram;

	int i;

	for (i = 0; i < 16; i++)
	{
		int code = *p++;
		int vpos = *p++;
		int hpos = *p++;
		int flag = *p++;

		int layout =
			((flag & 0xc0) == 0x80) ? 1 :
			((flag & 0xc0) == 0xc0) ? 2 : 0;

		int flip_x = code & 0x40;
		int flip_y = code & 0x80;

		int zoom_x = 0x10000;
		int zoom_y = 0x10000;

		code &= 0x3f;

		if (flag & 1)
		{
			code |= 0x40;
		}
		if (flag & 2)
		{
			zoom_x *= 2;
		}

		vpos = 240 - vpos;

		hpos <<= 1;
		vpos <<= 1;

		drawgfxzoom(bitmap, Machine->gfx[layout], code, 0, flip_x, flip_y,
			hpos, vpos, cliprect, TRANSPARENCY_PEN, 0, zoom_x, zoom_y);
	}
}
