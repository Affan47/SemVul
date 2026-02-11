SCR_CheckDrawIRCString (void)
{
	FNT_font_t		font;
	struct FNT_window_s	box;
	int			i , last_line;
	static float		color[ 4 ] = { 1 , 1 , 1 , 1 };

	scr_IRCtime_off -= cls.frametime;
	if (scr_IRCtime_off <= 0 || scr_IRC_display == SCR_IRC_DISPLAY_HIDE)
		return;

	last_line = ( scr_IRC_display == SCR_IRC_DISPLAY_FULL ) ? scr_IRC_lines : ( scr_IRC_lines - 1 );
	if ( last_line == -1 )
		return;

	font = FNT_AutoGet( CL_gameFont );

	box.x = 0;
	box.y = font->size * 5;
	for ( i = 0 ; i <= last_line ; i++ ) {
		box.width = viddef.width;
		box.height = font->size * 15 - box.y;

		FNT_WrappedPrint( font , scr_IRCstring[ i ] , FNT_CMODE_QUAKE , FNT_ALIGN_LEFT ,
			SCR_IRC_INDENT , &box , color );

		box.y += box.height;
		if ( box.y >= font->size * 15 ) {
			break;
		}
	}
}
