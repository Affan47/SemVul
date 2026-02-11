draw_sprites(struct mame_bitmap *bitmap, const struct rectangle *cliprect)
{
	int offs;
	unsigned char *sr;

	if (*gberet_spritebank & 0x08)
		sr = spriteram_2;
	else sr = spriteram;

	for (offs = 0;offs < spriteram_size;offs += 4)
	{
		if (sr[offs+3])
		{
			int sx,sy,flipx,flipy;


			sx = sr[offs+2] - 2*(sr[offs+1] & 0x80);
			sy = sr[offs+3];
			flipx = sr[offs+1] & 0x10;
			flipy = sr[offs+1] & 0x20;

			if (flipscreen)
			{
				sx = 240 - sx;
				sy = 240 - sy;
				flipx = !flipx;
				flipy = !flipy;
			}

			drawgfx(bitmap,Machine->gfx[1],
					sr[offs+0] + ((sr[offs+1] & 0x40) << 2),
					sr[offs+1] & 0x0f,
					flipx,flipy,
					sx,sy,
					cliprect,TRANSPARENCY_COLOR,0);
		}
	}
}
