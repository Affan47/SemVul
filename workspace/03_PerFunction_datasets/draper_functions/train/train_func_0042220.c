SCR_showTimer(void)
{
	static char		temptime[ 32 ];
	static int		timecounter;
	FNT_font_t		font;

	if (cls.key_dest == key_menu || cls.key_dest == key_console)
		return;

	if ((cls.realtime + 2000) < timecounter)
		timecounter = cl.time + 1000;

	if (cls.realtime > timecounter)
	{
		seconds += 1;
		if(seconds >= 60) {
			minutes++;
			seconds = 0;
		}
		Com_sprintf(temptime, sizeof(temptime),"%i:%2.2i", minutes, seconds);
		timecounter = cls.realtime + 1000;
	}

	font = FNT_AutoGet( CL_gameFont );
	Draw_StretchPic( viddef.width - 13 * font->size , viddef.height - 5.25 * font->size , 4 * font->size , 4 * font->size , "timer");
	FNT_RawPrint( font , temptime , strlen( temptime ) , false ,
		viddef.width - 8 * font->size , viddef.height - 3.75 * font->size , FNT_colors[ 7 ] );
}
