AtopCompositePixels(void *mutable_data,
                    const void *immutable_data,
                    const Image *source_image,
                    const PixelPacket *source_pixels,
                    const IndexPacket *source_indexes,
                    Image *update_image,
                    PixelPacket *update_pixels,
                    IndexPacket *update_indexes,
                    const long npixels,
                    ExceptionInfo *exception
                    )
{
  register long
    i;

  PixelPacket
    destination,
    source;

  ARG_NOT_USED(mutable_data);
  ARG_NOT_USED(immutable_data);
  ARG_NOT_USED(exception);


  for (i=0; i < npixels; i++)
    {
      PrepareSourcePacket(&source,source_pixels,source_image,source_indexes,i);
      PrepareDestinationPacket(&destination,update_pixels,update_image,update_indexes,i);

      AtopCompositePixel(&destination,&destination,&source);

      ApplyPacketUpdates(update_pixels,update_indexes,update_image,&destination,i);
    }

  return MagickPass;
}
