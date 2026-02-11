loadtile(int tileset)
{


  SDL_FillRect(GFX_lpDDSTwo, NULL, SDL_MapRGB(GFX_lpDDSTwo->format, 0, 0, 0));

  spr[1].seq = 3; spr[1].seq_orig = 3;

  if (mode == MODE_SCREEN_TILES)
    {
      m3x = spr[1].x; m3y = spr[1].y;
      spr[1].x = m2x; spr[1].y = m2y; mode = 2;
      spr[1].speed = 50;
    }


  if (mode == MODE_TILE_HARDNESS)
    {
      spr[1].x = m2x; spr[1].y = m2y; mode = 2;
      spr[1].speed = 50;
    }


  SDL_BlitSurface(gfx_tiles[tileset], NULL, GFX_lpDDSTwo, NULL);
  cur_screen = tileset;

  last_mode = tileset;

  while(kill_last_sprite());
}
