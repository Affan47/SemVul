splash_draw_sprites(struct mame_bitmap *bitmap,const struct rectangle *cliprect)
{
	int i;
	const struct GfxElement *gfx = Machine->gfx[1];

	for (i = 0; i < 0x400; i += 4){
		int sx = splash_spriteram[i+2] & 0xff;
		int sy = (240 - (splash_spriteram[i+1] & 0xff)) & 0xff;
		int attr = splash_spriteram[i+3] & 0xff;
		int attr2 = splash_spriteram[i+0x400] >> 8;
		int number = (splash_spriteram[i] & 0xff) + (attr & 0xf)*256;

		if (attr2 & 0x80) sx += 256;

		drawgfx(bitmap,gfx,number,
			0x10 + (attr2 & 0x0f),attr & 0x40,attr & 0x80,
			sx-8,sy,
			cliprect,TRANSPARENCY_PEN,0);
	}
}
