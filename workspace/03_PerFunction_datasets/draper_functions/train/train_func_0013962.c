tiles_load_slot(char* relpath, int slot)
{
  FILE* in = paths_dmodfile_fopen(relpath, "rb");
  if (in == NULL)
    in = paths_fallbackfile_fopen(relpath, "rb");

  if (gfx_tiles[slot] != NULL)
    {
      SDL_FreeSurface(gfx_tiles[slot]);
      gfx_tiles[slot] = NULL;
    }

  gfx_tiles[slot] = load_bmp_from_fp(in);


  if (gfx_tiles[slot] == NULL) {
    fprintf(stderr, "Couldn't find tilescreen %s: %s\n", relpath, SDL_GetError());
  }
}
