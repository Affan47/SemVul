AcquirePixelThreadSet(const size_t count)
{
  RealPixelPacket
    **pixels;

  register ssize_t
    i;

  size_t
    number_threads;

  number_threads=(size_t) GetMagickResourceLimit(ThreadResource);
  pixels=(RealPixelPacket **) AcquireQuantumMemory(number_threads,
    sizeof(*pixels));
  if (pixels == (RealPixelPacket **) NULL)
    return((RealPixelPacket **) NULL);
  (void) ResetMagickMemory(pixels,0,number_threads*sizeof(*pixels));
  for (i=0; i < (ssize_t) number_threads; i++)
  {
    pixels[i]=(RealPixelPacket *) AcquireQuantumMemory(count,
      2*sizeof(**pixels));
    if (pixels[i] == (RealPixelPacket *) NULL)
      return(DestroyPixelThreadSet(pixels));
  }
  return(pixels);
}
