tile_decode(int uses_5bpp_tiles)
{
	unsigned char lsb,msb;
	unsigned int offset,i;
	UINT8 *gfx = memory_region(REGION_GFX2);
	int size=memory_region_length(REGION_GFX2);
	int half=size/2,data;


	if (uses_5bpp_tiles)
		for (i=half; i<size; i+=2)
			gfx[i+1]=0;

	offset = size/2;
	for (i = size/2+size/4; i<size; i+=2)
	{

		lsb = gfx[i+1];
		msb = gfx[i];

		gfx[offset+0]=((msb&0x02)<<3) | ((msb&0x01)>>0) | ((lsb&0x02)<<4) | ((lsb&0x01)<<1);
		gfx[offset+2]=((msb&0x08)<<1) | ((msb&0x04)>>2) | ((lsb&0x08)<<2) | ((lsb&0x04)>>1);
		gfx[offset+1]=((msb&0x20)>>1) | ((msb&0x10)>>4) | ((lsb&0x20)<<0) | ((lsb&0x10)>>3);
		gfx[offset+3]=((msb&0x80)>>3) | ((msb&0x40)>>6) | ((lsb&0x80)>>2) | ((lsb&0x40)>>5);

		offset+=4;
	}

	gfx = memory_region(REGION_GFX1);
	size=memory_region_length(REGION_GFX1);

	offset = size/2;
	for (i = size/2+size/4; i<size; i++)
	{
		int d1,d2,d3,d4;


		data = gfx[i];
		d1 = (data>>0) & 3;
		d2 = (data>>2) & 3;
		d3 = (data>>4) & 3;
		d4 = (data>>6) & 3;

		gfx[offset] = (d1<<2) | (d2<<6);
		offset++;

		gfx[offset] = (d3<<2) | (d4<<6);
		offset++;
	}
	state_save_register_UINT32("f3", 0, "coinword", coin_word, 2);
}
