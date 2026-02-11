Parse_font(SDL_Surface * image, byte * font)
{
  int character;
  byte color;
  int x, y;
  int chars_per_line;


  if (image->w % 8)
  {
    sprintf(Gui_loading_error_message, "Error in font file: Image width is not a multiple of 8.\n");
    return 1;
  }
  if (image->w * image->h < 8*8*256)
  {
    sprintf(Gui_loading_error_message, "Error in font file: Image is too small to be a 256-character 8x8 font.\n");
    return 1;
  }
  chars_per_line = image->w/8;

  for (character=0; character < 256; character++)
  {
    for (y=0; y<8; y++)
    {
      for (x=0;x<8; x++)
      {

        color = Get_SDL_pixel_8(image, (character % chars_per_line)*8+x, (character / chars_per_line)*8+y);
        if (color > 1)
        {
          sprintf(Gui_loading_error_message, "Error in font file: Only colors 0 and 1 can be used for the font.\n");
          return 1;
        }

        font[character*64 + y*8 + x]=color;
      }
    }
  }
  return 0;
}
