UpdatePalette( void )
{
	int bank;
	for( bank=0; bank<0x20; bank++ )
	{
		int pen = bank*256;
		int offset = ((pen & 0x1800) << 2) | (pen & 0x07ff);
		int i;
		for( i=0; i<256; i++ )
		{
			int r = namcos2_68k_palette_ram[offset | 0x0000] & 0x00ff;
			int g = namcos2_68k_palette_ram[offset | 0x0800] & 0x00ff;
			int b = namcos2_68k_palette_ram[offset | 0x1000] & 0x00ff;
			palette_set_color(pen++,r,g,b);
			offset++;
		}
	}
}
