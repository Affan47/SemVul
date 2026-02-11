set_help(int x1, int y1, int x2, int y2, const char* helpCode)
{
	err_when( strlen(helpCode) > 8 );

	if( !mouse.in_area(x1, y1, x2, y2) )
		return;

	strcpy( help_code, helpCode );

	help_x = (x1+x2)/2;
	help_y = (y1+y2)/2;
}
