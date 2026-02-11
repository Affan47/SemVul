field(int xDes, int y1, const char* desStr, int xValue, double value,
					  int format, int xEnd, int refreshFlag, char* helpCode )
{
	int x2;

   if( refreshFlag == INFO_REPAINT )
   {
		vga_util.d3_panel_up( xDes, y1, xValue, y1+font_height+3 );

      put( xDes+2  , y1+2, desStr);
      x2 = put( xValue+4, y1+2, misc.format(value,format) );
   }
   else
   {
		x2 = put( xValue+4, y1+2, misc.format(value,format), 1, xEnd );
	}

	if( helpCode )
		help.set_help(xDes, y1, x2, y1+font_height+3, helpCode );
}
