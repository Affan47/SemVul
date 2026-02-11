ninjaw_draw_sprites(struct mame_bitmap *bitmap,const struct rectangle *cliprect,int primask,int y_offs)
{
	int offs, data, tilenum, color, flipx, flipy;
	int x, y, priority, invis, curx, cury;
	int code;

#ifdef MAME_DEBUG
	int unknown=0;
#endif


	struct tempsprite *sprite_ptr = spritelist;

	for (offs = (spriteram_size/2)-4;offs >=0;offs -= 4)
	{
		data = spriteram16[offs+2];
		tilenum = data & 0x7fff;

		if (!tilenum) continue;

		data = spriteram16[offs+0];

		x = (data - 32) & 0x3ff;

		data = spriteram16[offs+1];
		y = (data - 0) & 0x1ff;


		data = spriteram16[offs+3];
		flipx    = (data & 0x1);
		flipy    = (data & 0x2) >> 1;
		priority = (data & 0x4) >> 2;
		if (priority != primask) continue;
		invis    = (data & 0x8) >> 3;
		color    = (data & 0x7f00) >> 8;


#ifdef MAME_DEBUG
		if (data & 0x80f0)   unknown |= (data &0x80f0);
#endif

		y += y_offs;


		if (x>0x3c0) x -= 0x400;
		if (y>0x180) y -= 0x200;

		curx = x;
		cury = y;
		code = tilenum;

		sprite_ptr->code = code;
		sprite_ptr->color = color;
		sprite_ptr->flipx = flipx;
		sprite_ptr->flipy = flipy;
		sprite_ptr->x = curx;
		sprite_ptr->y = cury;

		drawgfx(bitmap,Machine->gfx[0],
				sprite_ptr->code,
				sprite_ptr->color,
				sprite_ptr->flipx,sprite_ptr->flipy,
				sprite_ptr->x,sprite_ptr->y,
				cliprect,TRANSPARENCY_PEN,0);
	}

#ifdef MAME_DEBUG
	if (unknown)
		usrintf_showmessage("unknown sprite bits: %04x",unknown);
#endif
}
