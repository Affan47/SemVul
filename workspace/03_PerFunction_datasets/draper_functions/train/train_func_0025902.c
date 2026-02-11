_CON_DrawConsoleBottom( int y )
{
	FNT_font_t	font;
	char		buffer[ MAX_STRING_CHARS ];
	int		kb , sz;

	font = FNT_AutoGet( CL_gameFont );
	y -= font->size;


	sz = sizeof( VERSION );
	FNT_RawPrint( font , VERSION , sz , false ,
		viddef.width - font->size * 5 * sz / 2 , y , FNT_colors[ 7 ] );


	if ( ! ( cls.download && ( kb = (int)ftell( cls.download ) / 1024 ) ) ) {
		return y;
	}

	Com_sprintf( buffer , MAX_STRING_CHARS , "Downloading %s [%s] ... %dKB" ,
		cls.downloadname , ( cls.downloadhttp ? "HTTP" : "UDP" ), kb );
	FNT_RawPrint( font , buffer , strlen( buffer ) , false ,
		font->size * 3 , y , FNT_colors[ 3 ] );

	return y;
}
