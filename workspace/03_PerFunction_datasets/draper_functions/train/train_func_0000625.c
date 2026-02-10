mapper9_latch( offs_t offset )
{
	if( (offset & 0x1ff0) == 0x0fd0 && MMC2_bank_latch[0] != 0xfd )
	{
		MMC2_bank_latch[0] = 0xfd;
		ppu2c03b_set_videorom_bank( 0, 0, 4, MMC2_bank[0], 256 );
	}
	else if( (offset & 0x1ff0) == 0x0fe0 && MMC2_bank_latch[0] != 0xfe )
	{
		MMC2_bank_latch[0] = 0xfe;
		ppu2c03b_set_videorom_bank( 0, 0, 4, MMC2_bank[1], 256 );
	}
	else if( (offset & 0x1ff0) == 0x1fd0 && MMC2_bank_latch[1] != 0xfd )
	{
		MMC2_bank_latch[1] = 0xfd;
		ppu2c03b_set_videorom_bank( 0, 4, 4, MMC2_bank[2], 256 );
	}
	else if( (offset & 0x1ff0) == 0x1fe0 && MMC2_bank_latch[1] != 0xfe )
	{
		MMC2_bank_latch[1] = 0xfe;
		ppu2c03b_set_videorom_bank( 0, 4, 4, MMC2_bank[3], 256 );
	}
}
