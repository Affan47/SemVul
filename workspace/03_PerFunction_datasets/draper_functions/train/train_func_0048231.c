getPrintBitmap(void *bitmap,
                                                unsigned long size,
                                                OFBool inversePLUT)
{
  OFCondition result = EC_IllegalCall;
  if ((bitmap != NULL) && (size == getPrintBitmapSize()))
  {
    if (currentImage)
    {
      renderPixelData(OFFalse);
      unsigned long width;
      unsigned long height;
      if (getPrintBitmapWidthHeight(width, height) == EC_Normal)
      {
        DicomImage *image = currentImage;


        if (presentationLUT.getType() == DVPSP_table)
        {
          if (inversePLUT)
          {
            if (currentImageMonochrome1) currentImage->setPolarity(EPP_Reverse);
            presentationLUT.activateInverseLUT(currentImage);
          } else {

            if (currentImageMonochrome1) currentImage->setPresentationLutShape(ESP_Inverse);
            else currentImage->setPresentationLutShape(ESP_Identity);
          }

          currentImagePLUTValid = OFFalse;
        }


        if ((renderedImageLeft != 1) || (renderedImageRight != (signed long)renderedImageWidth) ||
            (renderedImageTop != 1) || (renderedImageBottom != (signed long)renderedImageHeight))
        {
          DicomImage *img = currentImage->createMonoOutputImage(currentImageSelectedFrame-1, 12 );
          if (img == NULL)
            img = currentImage;
          image = img->createClippedImage(renderedImageLeft - 1, renderedImageTop - 1, renderedImageRight - renderedImageLeft + 1,
            renderedImageBottom - renderedImageTop + 1, getShutterPresentationValue());
          if (img != currentImage)
            delete img;
        }

        if (((signed long)width != renderedImageRight - renderedImageLeft + 1) ||
           ((signed long)height != renderedImageBottom - renderedImageTop + 1))
        {
          DicomImage *img = image;
          image = img->createScaledImage(width, height, 0 , 0 );
          if (img != currentImage)
            delete img;
        }
        if (image != NULL)
        {
          if (image->getOutputData(bitmap, size, 12 , currentImageSelectedFrame-1)) result = EC_Normal;
        }
        if (image != currentImage) delete image;
      }
    }
  }
  return result;
}
