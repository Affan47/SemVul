InCompositePixels(void *mutable_data,
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

      if (source.opacity == TransparentOpacity)
        {
          destination=source;
        }
      else if (destination.opacity == TransparentOpacity)
        {
        }
      else
        {
          double
            opacity;

          opacity=(double)
            (((double) MaxRGBDouble-source.opacity)*
             (MaxRGBDouble-destination.opacity)/MaxRGBDouble);

          destination.red=(Quantum)
            (((double) MaxRGBDouble-source.opacity)*
             (MaxRGBDouble-destination.opacity)*source.red/MaxRGBDouble/opacity+0.5);

          destination.green=(Quantum)
            (((double) MaxRGBDouble-source.opacity)*
             (MaxRGBDouble-destination.opacity)*source.green/MaxRGBDouble/opacity+0.5);

          destination.blue=(Quantum)
            (((double) MaxRGBDouble-source.opacity)*
             (MaxRGBDouble-destination.opacity)*source.blue/MaxRGBDouble/opacity+0.5);

          destination.opacity=(Quantum) (MaxRGBDouble-opacity+0.5);
        }

      ApplyPacketUpdates(update_pixels,update_indexes,update_image,&destination,i);
    }

  return MagickPass;
}
