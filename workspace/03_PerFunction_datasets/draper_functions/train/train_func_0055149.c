get_youjyudn_bg_tile_info( int offs )
{
	int code;
	int color;
	code = m62_tileram[ offs << 1 ];
	color = m62_tileram[ ( offs << 1 ) | 1 ];
	SET_TILE_INFO( 0, code | ( ( color & 0x60 ) << 3 ), color & 0x1f, 0 );
	if( ( ( color & 0x1f ) >> 1 ) >= 0x08 )
	{
		tile_info.priority = 1;
	}
	else
	{
		tile_info.priority = 0;
	}
}
