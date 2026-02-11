PalettesAreEqual(Image *a,Image *b)
{
  long
    i;

  if ((a == (Image *) NULL) || (b == (Image *) NULL))
    return(MagickFail);
  if (a->storage_class!=PseudoClass || b->storage_class!=PseudoClass)
    return(MagickFail);
  if (a->colors != b->colors)
    return(MagickFail);
  for (i=0; i < (long) a->colors; i++)
    {
      if ((a->colormap[i].red != b->colormap[i].red) ||
          (a->colormap[i].green != b->colormap[i].green) ||
          (a->colormap[i].blue != b->colormap[i].blue))
        return(MagickFail);
    }
  return((int) MagickTrue);
}
