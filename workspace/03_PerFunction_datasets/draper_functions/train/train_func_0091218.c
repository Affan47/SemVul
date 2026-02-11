SetCursor( const Point &hex ) {
  Rect update( 0, 0, 0, 0 );

  if ( (hex.x == -1) && (hex.y == -1) ) {
    if ( CursorEnabled() ) {
      Point old = cursor;
      cursor = Point( -1, -1 );


      update = UpdateHex( old );
      SetFlags(MV_DISABLE_CURSOR);
    }
  } else {
    UnsetFlags(MV_DISABLE_CURSOR);
    cursor = hex;
    update = UpdateHex( hex );
    if ( FlagSet(MV_AUTOSCROLL) && CheckScroll() ) update = *this;
  }
  return update;
}
