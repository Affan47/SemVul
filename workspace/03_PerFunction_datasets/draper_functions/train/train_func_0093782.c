PushImagePixels(Image *image,const QuantumType quantum,
  const unsigned char *source)
{
  QuantumInfo
    *quantum_info;

  size_t
    length;

  quantum_info=AcquireQuantumInfo((const ImageInfo *) NULL,image);
  if (quantum_info == (QuantumInfo *) NULL)
    return(0);
  length=ImportQuantumPixels(image,(CacheView *) NULL,quantum_info,quantum,
    source,&image->exception);
  quantum_info=DestroyQuantumInfo(quantum_info);
  return(length);
}
