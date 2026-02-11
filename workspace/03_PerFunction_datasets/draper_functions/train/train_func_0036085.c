JustifiedPrintString (SDL_Surface * Surface, int y, char *fmt, ...)
{
  va_list args;
  char *temp;
  va_start (args, fmt);

  if ((temp = (char *) MyMalloc (1000 + 1)) != NULL)
    {
      vsprintf (temp, fmt, args);
      JustifiedPutString (Surface, y, temp);
      free (temp);
    }
  va_end (args);
}
