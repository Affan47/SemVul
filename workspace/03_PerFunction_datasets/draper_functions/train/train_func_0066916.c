niyanpai_gfxflag_w(int vram, int offset, int data)
{
	static int niyanpai_flipscreen_old[VRAM_MAX] = { -1, -1, -1 };

	niyanpai_gfxflag[vram] = data;

	niyanpai_flipx[vram] = (data & 0x01) ? 1 : 0;
	niyanpai_flipy[vram] = (data & 0x02) ? 1 : 0;
	niyanpai_highcolor[vram] = (data & 0x04) ? 1 : 0;

	niyanpai_transparency[vram] = (data & 0x10) ? 1 : 0;

	niyanpai_flipscreen[vram] = (data & 0x40) ? 0 : 1;
	niyanpai_dispflag[vram] = (data & 0x80) ? 1 : 0;

	if (niyanpai_flipscreen[vram] != niyanpai_flipscreen_old[vram])
	{
		niyanpai_screen_refresh = 1;
		niyanpai_flipscreen_old[vram] = niyanpai_flipscreen[vram];
		niyanpai_vramflip(vram);
	}
}
