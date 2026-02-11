draw_sprites1(struct mame_bitmap *bitmap, const struct rectangle *cliprect, int priority)
{
	int offs,x,y,sprite,sprite2,colour,extra,fx,fy;

	for (offs = 0;offs < 0x800;offs += 8)
	{
		y=buffered_spriteram[offs+1]+(buffered_spriteram[offs]<<8);
		if ((y&0x8000) == 0) continue;

        fx=buffered_spriteram[offs+3];

		if ((fx&0x1) == 0) continue;

		extra=fx&0x10;
        fy=fx&0x2;
        fx=fx&0x4;

		x = buffered_spriteram[offs+5]+(buffered_spriteram[offs+4]<<8);
		colour = buffered_spriteram[offs+6] >> 4;
		if (priority==1 && (colour&8)) continue;
		if (priority==2 && !(colour&8)) continue;
		sprite = buffered_spriteram[offs+7]+(buffered_spriteram[offs+6]<<8);
		sprite &= 0x0fff;

		if (extra) {y=y+16;sprite&=0xffe;}

		x = x & 0x01ff;
		y = y & 0x01ff;
		x=(x+16)%0x200;
		y=(y+16)%0x200;
		x=256 - x;
		y=256 - y;
		if (flip_screen) {
			y=240-y;
			x=240-x;
			if (fx) fx=0; else fx=1;
			if (fy) fy=0; else fy=1;
			if (extra) y=y-16;
		}


		if (extra && fy) {
			sprite2=sprite;
			sprite++;
		}
		else
			sprite2=sprite+1;

		drawgfx(bitmap,Machine->gfx[1],
				sprite,
				colour,fx,fy,x,y,
				cliprect,TRANSPARENCY_PEN,0);


    	if (extra)
    		drawgfx(bitmap,Machine->gfx[1],
				sprite2,
				colour,fx,fy,x,y+16,
				cliprect,TRANSPARENCY_PEN,0);
	}
}
