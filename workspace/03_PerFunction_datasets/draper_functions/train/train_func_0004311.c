rocnrope_draw_sprites( struct mame_bitmap *bitmap )
{
	int offs;

	for (offs = spriteram_size - 2;offs >= 0;offs -= 2)
	{
		drawgfx(bitmap,Machine->gfx[1],
				spriteram[offs + 1],
				spriteram_2[offs] & 0x0f,
				spriteram_2[offs] & 0x40,~spriteram_2[offs] & 0x80,
				240-spriteram[offs],spriteram_2[offs + 1],
				&Machine->visible_area,TRANSPARENCY_COLOR,0);
	}
}
