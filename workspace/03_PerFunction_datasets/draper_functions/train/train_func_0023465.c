nitedrvr_draw_road( struct mame_bitmap *bitmap )
{
	int roadway;

	for (roadway=0; roadway < 16; roadway++)
	{
		int bx, by, ex, ey;

		bx = nitedrvr_hvc[roadway];
		by = nitedrvr_hvc[roadway + 16];
		ex = bx + ((nitedrvr_hvc[roadway + 32] & 0xf0) >> 4);
		ey = by + (16 - (nitedrvr_hvc[roadway + 32] & 0x0f));

		nitedrvr_draw_block(bitmap,bx,by,ex,ey);
	}
}
