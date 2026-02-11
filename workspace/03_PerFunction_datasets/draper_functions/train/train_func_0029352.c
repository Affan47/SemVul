hyhoo_gfxflag1_w(int data)
{
	static int hyhoo_flipscreen_old = -1;

	hyhoo_gfxflag1 = data;

	hyhoo_flipx = (data & 0x01) ? 1 : 0;
	hyhoo_flipy = (data & 0x02) ? 1 : 0;
	hyhoo_flipscreen = (data & 0x04) ? 0 : 1;
	hyhoo_dispflag = (data & 0x08) ? 0 : 1;

	if ((nb1413m3_type == NB1413M3_HYHOO) ||
	    (nb1413m3_type == NB1413M3_HYHOO2))
	{
		hyhoo_flipscreen ^= 1;
	}

	if (hyhoo_flipscreen != hyhoo_flipscreen_old)
	{
		hyhoo_vramflip();
		hyhoo_screen_refresh = 1;
		hyhoo_flipscreen_old = hyhoo_flipscreen;
	}
}
