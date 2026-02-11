disp_version()
{


	String str;

	str  = "Version ";
	str += GAME_VERSION_STR;

	#ifdef DEMO
		str = "Demo Version";
	#endif

	#ifdef BETA
		str = "This is a Beta version. Unauthorized distribution of this Beta is illegal.";
	#endif

	if( str.len() > 40 )
		font_news.center_put( 0, VGA_HEIGHT-20, VGA_WIDTH-1, VGA_HEIGHT-1, str );
	else
		font_news.right_put( VGA_WIDTH-10, VGA_HEIGHT-20, str );
}
