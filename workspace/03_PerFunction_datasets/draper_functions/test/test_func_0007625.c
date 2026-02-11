zwackery_update_sprites(struct mame_bitmap *bitmap, const struct rectangle *cliprect, int priority)
{
	int offs;

	fillbitmap(priority_bitmap,1,cliprect);


	for (offs = spriteram_size / 2 - 4;offs >= 0;offs -= 4)
	{
		int code, color, flipx, flipy, x, y, flags;


		code = LOW_BYTE(spriteram16[offs + 2]);
		if (code == 0)
			continue;


		flags = LOW_BYTE(spriteram16[offs + 1]);
		color = ((~flags >> 2) & 0x0f) | ((flags & 0x02) << 3);


		if (!priority)
		{
			if (color == 7)
				continue;
		}


		else
		{
			if (color != 7)
				continue;
		}


		flipx = ~flags & 0x40;
		flipy = flags & 0x80;
		x = (231 - LOW_BYTE(spriteram16[offs + 3])) * 2;
		y = (241 - LOW_BYTE(spriteram16[offs])) * 2;

		if (x <= -32) x += 512;


		pdrawgfx(bitmap, Machine->gfx[1], code, color, flipx, flipy, x, y,
				cliprect, TRANSPARENCY_PENS, 0x0101, 0x00);


		pdrawgfx(bitmap, Machine->gfx[1], code, color, flipx, flipy, x, y,
				cliprect, TRANSPARENCY_PENS, 0xfeff, 0x02);
	}
}
