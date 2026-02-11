GetImageListIndex(const Image *images)
{
  if (images->debug != MagickFalse)
    (void) LogMagickEvent(DeprecateEvent,GetMagickModule(),"last use: v5.5.2");
  return(GetImageIndexInList(images));
}
