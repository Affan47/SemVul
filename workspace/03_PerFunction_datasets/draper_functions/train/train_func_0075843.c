update_dirty_rects( void )
{
  int start, y;

  for( y=0; y<DISPLAY_SCREEN_HEIGHT; y++ ) {
    int x = 0;
    while( display_is_dirty[y] ) {


      while( !( display_is_dirty[y] & 0x01 ) ) {
        display_is_dirty[y] >>= 1;
        x++;
      }

      start = x;


      do {
        display_is_dirty[y] >>= 1;
        x++;
      } while( display_is_dirty[y] & 0x01 );

      rectangle_add( y, start, x - start );
    }


    rectangle_end_line( y );
  }


  rectangle_end_line( DISPLAY_SCREEN_HEIGHT );
}
