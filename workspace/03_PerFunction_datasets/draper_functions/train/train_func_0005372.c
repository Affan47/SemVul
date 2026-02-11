draw_sprites(struct mame_bitmap *bitmap,const struct rectangle *cliprect)
{
	int offs,x,y,color,sprite,flipx,flipy;

	for (offs = 0x0800-4;offs >=0;offs -= 4)
	{

		x = spriteram16[offs+3]&0x1ff;
		if (x==0x180) continue;
		if (x>0xff) x=0-(0x200-x);
		y = 240-spriteram16[offs+2];
		color = ((spriteram16[offs+1]>>2)&0xf);
		sprite = spriteram16[offs]&0x7ff;

		flipx=spriteram16[offs+1]&2;
		flipy=spriteram16[offs+1]&1;

		drawgfx(bitmap,Machine->gfx[1],
				sprite,
                color,flipx,flipy,x,y,
				cliprect,TRANSPARENCY_PEN,15);
	}
}
