getPixelData(
     const void *&pixelData,
     unsigned long &width,
     unsigned long &height)
{
   if (currentImage)
   {
     renderPixelData();
     width = currentImage->getWidth();
     height = currentImage->getHeight();
     pixelData = currentImage->getOutputData(8, currentImageSelectedFrame-1);
   } else {
     pixelData = NULL;
     width = 0;
     height = 0;
     return EC_IllegalCall;
   }
   return EC_Normal;
}
