pstadium_gfxflag_w(int data)
{
	static int pstadium_flipscreen_old = -1;

	pstadium_flipx = (data & 0x01) ? 1 : 0;
	pstadium_flipy = (data & 0x02) ? 1 : 0;
	pstadium_flipscreen = (data & 0x04) ? 0 : 1;
	pstadium_dispflag = (data & 0x10) ? 0 : 1;

	if (pstadium_flipscreen != pstadium_flipscreen_old)
	{
		pstadium_vramflip();
		pstadium_screen_refresh = 1;
		pstadium_flipscreen_old = pstadium_flipscreen;
	}
}
