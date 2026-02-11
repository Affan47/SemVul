ConstrainPixel(Image *image,const ssize_t offset,
  const size_t extent)
{
  if ((offset < 0) || (offset > (ssize_t) extent))
    {
      (void) ThrowMagickException(&image->exception,GetMagickModule(),
        CorruptImageError,"InvalidPixel","`%s'",image->filename);
      return(0);
    }
  return(offset);
}
