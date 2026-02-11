load_cursors(void)
{
  enum cursor_type cursor;
  int frame;
  SDL_Surface *pSurf;

  pStd_Cursor = SDL_GetCursor();

  pSurf = create_surf_alpha(1, 1, SDL_SWSURFACE);
  pDisabledCursor = SurfaceToCursor(pSurf, 0, 0);
  FREESURFACE(pSurf);

  for (cursor = 0; cursor < CURSOR_LAST; cursor++) {
    for (frame = 0; frame < NUM_CURSOR_FRAMES; frame++) {
      int hot_x, hot_y;
      struct sprite *sprite
        = get_cursor_sprite(tileset, cursor, &hot_x, &hot_y, frame);

      pSurf = GET_SURF(sprite);

      fc_cursors[cursor][frame] = SurfaceToCursor(pSurf, hot_x, hot_y);
    }
  }
}
