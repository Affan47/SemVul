widget_text_draw_text( void )
{
  int width;
  const char *tptr;

  widget_rectangle( 12, 28, 232, 8, WIDGET_COLOUR_BACKGROUND );

  tptr = text - 1;
  do {
    width = widget_stringwidth (++tptr);
  } while (width > 28 * 8 - 4);

  if( tptr != text )
    widget_rectangle( 14, 29, 1, 6, 5 );

  widget_printstring( 16, 28, WIDGET_COLOUR_FOREGROUND, tptr );
  widget_rectangle( 17 + width, 35, 4, 1, 5 );

  widget_display_rasters( 28, 8 );
  return 0;
}
