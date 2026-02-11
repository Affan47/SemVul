gridiron_drawled(struct mame_bitmap *bitmap,UINT8 led,int player)
{
	int i;


	static UINT8 ledvalues[] =
			{ 0x86, 0xdb, 0xcf, 0xe6, 0xed, 0xfd, 0x87, 0xff, 0xf3, 0xf1 };


	if ((led & 0x80) == 0) return;

	for (i = 0;i < 10;i++)
	{
		if (led == ledvalues[i] ) break;
	}

	if (i < 10)
	{
		if (player == 0)
			drawgfx(bitmap,Machine->gfx[0],
					0xc0 + i,
					0x0a,
					0,0,
					0,232,
					&Machine->visible_area,TRANSPARENCY_NONE,0);
		else
			drawgfx(bitmap,Machine->gfx[0],
					0xc0 + i,
					0x03,
					1,1,
					0,16,
					&Machine->visible_area,TRANSPARENCY_NONE,0);
	}
else logerror("unknown LED %02x for player %d\n",led,player);
}
