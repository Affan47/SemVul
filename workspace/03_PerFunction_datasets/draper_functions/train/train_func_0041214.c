draw_sprites(struct mame_bitmap *bitmap, const struct rectangle *cliprect)
{
	const struct GfxElement *gfx = Machine->gfx[2];
	int offs;


	for (offs = spriteram_size - 4;offs >= 0;offs -= 4)
	{
		unsigned char attributes = buffered_spriteram[offs+1];
		int sx = buffered_spriteram[offs + 3] - 0x100 * (attributes & 0x01);
		int sy = buffered_spriteram[offs + 2];
		int flipx = attributes & 0x04;
		int flipy = attributes & 0x08;

		if (flip_screen)
		{
			sx = 240 - sx;
			sy = 240 - sy;
			flipx = !flipx;
			flipy = !flipy;
		}

		drawgfx(bitmap,gfx,
				buffered_spriteram[offs] + ((attributes<<2) & 0x300),
				(attributes >> 4) & 3,
				flipx,flipy,
				sx,sy,
				cliprect,TRANSPARENCY_PEN,15);
	}
}
