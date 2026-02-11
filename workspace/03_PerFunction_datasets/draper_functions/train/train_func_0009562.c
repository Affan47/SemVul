PutStringFont (SDL_Surface * Surface, BFont_Info * Font, int x, int y,
	       char *text)
{
  int i = 0;
  while (text[i] != '\0')
    {
      x += PutCharFont (Surface, Font, x, y, text[i]);
      i++;
    }
}
