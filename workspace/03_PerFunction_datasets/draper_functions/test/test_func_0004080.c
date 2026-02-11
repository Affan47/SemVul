CheckScroll( void ) {
  if ( cursor.x == -1 ) return false;

  Point p = Hex2Pixel( cursor );

  if ( (curx > 0) && (p.x <= x + TileWidth()) ) p.x = -w / 2;
  else if ( (curx < maxx) && (w + x - p.x - TileWidth() <= TileWidth()) )
    p.x = w / 2;
  else p.x = 0;

  if ( (cury > 0) && (p.y <= y + TileHeight()) ) p.y = -h / 2;
  else if ( (cury < maxy) && (h + y - p.y - TileHeight() <= TileHeight()) )
    p.y = h / 2;
  else p.y = 0;

  if ( p.x || p.y ) {
    Scroll( p.x, p.y );
    return true;
  }
  return false;
}
