aquarium_draw_sprites(struct mame_bitmap *bitmap,const struct rectangle *cliprect,int y_offs)
{
	int offs,chain_pos;
	int x,y,curx,cury;
	int priority=0;
	UINT8 col,flipx,flipy,chain;
	UINT16 code;


	priority = (aquarium_priority[0x0/2] & 0x8800) ? 0 : 1;

	for (offs = spriteram_size/2-8;offs >= 0;offs -= 8)
	{
		code = ((spriteram16[offs+5])&0xff) + (((spriteram16[offs+6]) &0xff) << 8);
		code &= 0x3fff;

		if (!(spriteram16[offs+4] &0x80))
		{
			x = ((spriteram16[offs+0]) &0xff) + (((spriteram16[offs+1]) &0xff) << 8);
			y = ((spriteram16[offs+2]) &0xff) + (((spriteram16[offs+3]) &0xff) << 8);


			if (x & 0x8000)  x -= 0x10000;
			if (y & 0x8000)  y -= 0x10000;

			col  =   ((spriteram16[offs+7]) &0x0f);
			chain =   (spriteram16[offs+4]) &0x07;
			flipy =   (spriteram16[offs+4]) &0x10;
			flipx =   (spriteram16[offs+4]) &0x20;

			curx = x;
			cury = y;

			if (((spriteram16[offs+4]) &0x08) && flipy)
				cury += (chain * 16);

			if (!(((spriteram16[offs+4]) &0x08)) && flipx)
				curx += (chain * 16);


			for (chain_pos = chain;chain_pos >= 0;chain_pos--)
			{
				pdrawgfx(bitmap, Machine->gfx[0],
						code,
						col,
						flipx, flipy,
						curx,cury,
						cliprect,TRANSPARENCY_PEN,0,
						priority ? 0xfc : 0xf0);

				code++;

				if ((spriteram16[offs+4]) &0x08)
				{
					if (flipy)	cury -= 16;
					else cury += 16;
				}
				else
				{
					if (flipx)	curx -= 16;
					else curx += 16;
				}
			}
		}
	}
#if 0
	if (rotate)
	{
		char buf[80];
		sprintf(buf,"sprite rotate offs %04x ?",rotate);
		usrintf_showmessage(buf);
	}
#endif
}
