ppu2c03b_spriteram_dma( int num, const UINT8 *source )
{

	if ( num >= intf->num )
	{
		logerror( "PPU(render): Attempting to access an unmapped chip\n" );
		return;
	}

	memcpy( chips[num].spriteram, source, SPRITERAM_SIZE );
}
