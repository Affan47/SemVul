imProcessConvolveRep(const imImage* src_image, imImage* dst_image, const imImage *kernel, int ntimes)
{
  imImage *AuxImage = imImageClone(dst_image);
  if (!AuxImage)
    return 0;

  int counter = imProcessCounterBegin("Repeated Convolution");
  const char* msg = (const char*)imImageGetAttribute(kernel, "Description", NULL, NULL);
  if (!msg) msg = "Filtering...";
  imCounterTotal(counter, src_image->depth*src_image->height*ntimes, msg);

  const imImage *image1 = src_image;
  imImage *image2 = dst_image;

  for (int i = 0; i < ntimes; i++)
  {
    if (!DoConvolveStep(image1, image2, kernel, counter))
    {
      imProcessCounterEnd(counter);
      imImageDestroy(AuxImage);
      return 0;
    }

    image1 = image2;

    if (image1 == dst_image)
      image2 = AuxImage;
    else
      image2 = dst_image;
  }


  if (image1 == AuxImage)
  {
    void** temp = (void**)dst_image->data;
    dst_image->data = AuxImage->data;
    AuxImage->data = (void**)temp;
  }

  imProcessCounterEnd(counter);
  imImageDestroy(AuxImage);

  return 1;
}
