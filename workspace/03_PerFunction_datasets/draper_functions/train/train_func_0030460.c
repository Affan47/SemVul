MoveCursor( int key ) {
  Direction dir;

  switch ( key ) {
  case SDLK_KP1:  dir = SOUTHWEST; break;
  case SDLK_DOWN:
  case SDLK_KP2:  dir = SOUTH;     break;
  case SDLK_KP3:  dir = SOUTHEAST; break;
  case SDLK_KP7:  dir = NORTHWEST; break;
  case SDLK_UP:
  case SDLK_KP8:  dir = NORTH;     break;
  case SDLK_KP9:  dir = NORTHEAST; break;
  case SDLK_LEFT:
  case SDLK_KP4:  dir = WEST;      break;
  case SDLK_RIGHT:
  case SDLK_KP6:  dir = EAST;      break;
  default: return;
  }

  Point dest;
  if ( !mv.GetMap()->Dir2Hex( mv.Cursor(), dir, dest ) ) SetCursor( dest );
}
