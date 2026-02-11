ChangeImageColour(wxImage * srcImage,
                           wxColour & srcColour,
                           wxColour & dstColour)
{


   unsigned char *src = srcImage->GetData();
   int width = srcImage->GetWidth();
   int height = srcImage->GetHeight();

   wxImage * dstImage = new wxImage(width, height);
   unsigned char *dst = dstImage->GetData();


   int srcVal[3], srcOpp[3];
   srcVal[0] = srcColour.Red();
   srcVal[1] = srcColour.Green();
   srcVal[2] = srcColour.Blue();

   int dstVal[3], dstOpp[3];
   dstVal[0] = dstColour.Red();
   dstVal[1] = dstColour.Green();
   dstVal[2] = dstColour.Blue();

   int i;
   for (i = 0; i < 3; i++) {
      srcOpp[i] = 256 - srcVal[i];
      dstOpp[i] = 255 - dstVal[i];
   }

   int c = 0;
   for (i = 0; i < width * height * 3; i++) {
      int s = (int) *src;

      if (s >= srcVal[c])
         *dst++ = dstVal[c] + dstOpp[c] * (s - srcVal[c]) / srcOpp[c];

      else
         *dst++ = dstVal[c] * s / srcVal[c];
      src++;
      c = (c + 1) % 3;
   }

   return dstImage;
}
