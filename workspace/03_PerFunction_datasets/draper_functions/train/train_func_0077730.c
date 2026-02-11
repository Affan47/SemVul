M_Credits_MenuDraw (menuframework_s *dummy, menuvec2_t offset)
{
	int i, y, scale;
	FNT_font_t		font;
	struct FNT_window_s	box;

	font = FNT_AutoGet( CL_menuFont );
	scale = font->size / 8.0;


	for ( i = 0, y = viddef.height - ( ( cls.realtime - credits_start_time ) / 40.0F ); credits[i]; y += 12*scale, i++ )
	{
		if ( y <= -12*scale )
			continue;

		box.y = offset.y + y;
		box.x = offset.x;
		box.height = 0;
		box.width = viddef.width;

		if ( credits[i][0] == '+' )
		{
			FNT_BoundedPrint (font, credits[i]+1, FNT_CMODE_NONE, FNT_ALIGN_CENTER, &box, FNT_colors[3]);
		}
		else
		{
			FNT_BoundedPrint (font, credits[i], FNT_CMODE_NONE, FNT_ALIGN_CENTER, &box, FNT_colors[7]);
		}
	}

	if ( y < 0 )
		credits_start_time = cls.realtime;
}
