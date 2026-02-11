ImageClassDestroy(closure)
void *closure;
{
  ImageClass *ic = (ImageClass *)closure;
  int i;

  ic->refcount--;
  if (ic->refcount > 0) return;

  free_mem(ic->colorcube);
  free_mem(ic->grayscale);
  for (i = 0; i < TCOUNT; i++)
  {
    if (ic->color_tables[i].generic_dither_table != NULL)
    {
      free_mem(ic->color_tables[i].generic_dither_table);
    }
  }
  for (i = 0; i < TCOUNT; i++)
  {
    if (ic->gray_tables[i].generic_dither_table != NULL)
    {
      free_mem(ic->gray_tables[i].generic_dither_table);
    }
  }
  MPDestroy(ic->mp);

  return;
}
