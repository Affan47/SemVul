make_display (int width, int height)
{
  register int i;
  DISPLAY_LINE **display;

  display = xmalloc ((1 + height) * sizeof (DISPLAY_LINE *));

  for (i = 0; i < height; i++)
    {
      display[i] = xmalloc (sizeof (DISPLAY_LINE));
      display[i]->text = xmalloc (1 + width);
      display[i]->textlen = 0;
      display[i]->inverse = 0;
    }
  display[i] = NULL;
  return display;
}
