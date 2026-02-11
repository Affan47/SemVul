printf_SDL (SDL_Surface *screen, int x, int y, char *fmt, ...)
{
  va_list args;
  int i, h, textlen;


  va_start (args, fmt);

  if (x == -1) x = MyCursorX;
  else MyCursorX = x;

  if (y == -1) y = MyCursorY;
  else MyCursorY = y;

  vsprintf (TextBuffer, fmt, args);
  textlen = 0;
  for (i=0; i < strlen(TextBuffer); i++)
    textlen += CharWidth (GetCurrentFont(), TextBuffer[i]);

  PutString (screen, x, y, TextBuffer);
  h = FontHeight (GetCurrentFont()) + 2;

  SDL_UpdateRect (screen, x, y, textlen, h);

  if (TextBuffer[strlen(TextBuffer)-1] == '\n')
    {
      MyCursorX = x;
      MyCursorY = y+ 1.1*h;
    }
  else
    {
      MyCursorX += textlen;
      MyCursorY = y;
    }

  va_end (args);
}
