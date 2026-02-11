AcquireStreamInfo(const ImageInfo *image_info)
{
  StreamInfo
    *stream_info;

  stream_info=(StreamInfo *) AcquireMagickMemory(sizeof(*stream_info));
  if (stream_info == (StreamInfo *) NULL)
    ThrowFatalException(ResourceLimitFatalError,"MemoryAllocationFailed");
  (void) ResetMagickMemory(stream_info,0,sizeof(*stream_info));
  stream_info->pixels=(unsigned char *) AcquireMagickMemory(
    sizeof(*stream_info->pixels));
  if (stream_info->pixels == (unsigned char *) NULL)
    ThrowFatalException(ResourceLimitFatalError,"MemoryAllocationFailed");
  stream_info->map=ConstantString("RGB");
  stream_info->storage_type=CharPixel;
  stream_info->stream=AcquireImage(image_info);
  stream_info->signature=MagickSignature;
  return(stream_info);
}
