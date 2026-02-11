TC0100SCN_tilemap_draw(struct mame_bitmap *bitmap,const struct rectangle *cliprect,int chip,int layer,int flags,UINT32 priority)
{
	int disable = TC0100SCN_ctrl[chip][6] & 0xf7;
	struct rectangle clip = *cliprect;
	sect_rect(&clip, &TC0100SCN_cliprect[chip]);

#if 0
if (disable != 0 && disable != 3 && disable != 7)
	usrintf_showmessage("layer disable = %x",disable);
#endif

	switch (layer)
	{
		case 0:
			if (disable & 0x01) return 1;
			tilemap_draw(bitmap,&clip,TC0100SCN_tilemap[chip][0][TC0100SCN_dblwidth[chip]],flags,priority);
			break;
		case 1:
			if (disable & 0x02) return 1;
			tilemap_draw(bitmap,&clip,TC0100SCN_tilemap[chip][1][TC0100SCN_dblwidth[chip]],flags,priority);
			break;
		case 2:
			if (disable & 0x04) return 1;
			tilemap_draw(bitmap,&clip,TC0100SCN_tilemap[chip][2][TC0100SCN_dblwidth[chip]],flags,priority);
			break;
	}
	return 0;
}
