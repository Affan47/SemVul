Menu_DrawStatusBar( const char *string )
{
	FNT_font_t		font;

	font = FNT_AutoGet( CL_menuFont );

	if ( string )
	{
		Draw_Fill (0, VID_HEIGHT-font->size-10, VID_WIDTH, font->size+10, RGBA(0.25, 0.25, 0.25, 1));
		Menu_DrawString (VID_WIDTH/2, VID_HEIGHT-font->size-5, string, FNT_CMODE_QUAKE, FNT_ALIGN_CENTER, light_color);
	}
}
