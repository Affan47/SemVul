argus_write_dummy_rams( int dramoffs, int vromoffs )
{
	int i;
	int voffs;
	int offs;

	data8_t *VROM1 = memory_region( REGION_USER1 );
	data8_t *VROM2 = memory_region( REGION_USER2 );


	offs = VROM1[ vromoffs ] | ( VROM1[ vromoffs + 1 ] << 8 );
	offs &= 0x7ff;

	voffs = offs * 16;
	for (i = 0 ; i < 8 ; i ++)
	{
		argus_dummy_bg0ram[ dramoffs ] = VROM2[ voffs ];
		argus_dummy_bg0ram[ dramoffs + 1 ] = VROM2[ voffs + 1 ];
		tilemap_mark_tile_dirty( bg0_tilemap, dramoffs >> 1 );
		dramoffs += 2;
		voffs += 2;
	}
}
