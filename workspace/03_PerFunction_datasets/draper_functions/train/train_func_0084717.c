SetupAutoplay(char *colourName)
{
  if (!strcmp(colourName, "black"))
    computer = BLACK;
  else if (!strcmp(colourName, "white"))
    computer = WHITE;
  else
    {
      return FALSE;
    }
  return TRUE;
}
