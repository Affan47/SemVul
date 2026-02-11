draw_sprites2(struct mame_bitmap *bitmap, const struct rectangle *cliprect, int c, int d, int yshift)
{
	int data, offs, mx, my, tile, color, fy, i;
	UINT8 *color_prom = memory_region(REGION_USER1);
	struct GfxElement *gfx = Machine->gfx[0];

	for (offs=0; offs<0x400; offs+=0x20)
	{
		mx = spriteram16[offs+c];
		my = (yshift-(mx>>8)) & 0xff;
		mx &= 0xff;

		for (i=0; i<0x20; i++)
		{
			data = spriteram16[offs+d+i];
			tile = data & 0x3fff;
			fy = data & 0x4000;
			color = color_prom[tile<<1|data>>15];

			drawgfx(bitmap, gfx, tile, color, 0, fy, mx, my,
					cliprect, TRANSPARENCY_PEN, 0);

			my = (my + 8) & 0xff;
		}
	}
}
