sa_get_contrast(int px, int py)
{
   int         map[4][2] = { {1, 0}, {1, 1}, {0, 1}, {-1, 1} };
   int         ii, qx, qy;
   uint16      *pix1, *pix2;
   double      red, green, blue;
   double      contrast, maxcontrast = 0;
   double      f65k = 1.0 / 65535.0;

   if (px < 1 || px > Fww-2) return 0;
   if (py < 1 || py > Fhh-2) return 0;

   for (ii = 0; ii < 4; ii++)
   {
      qx = map[ii][0];
      qy = map[ii][1];
      pix1 = PXMpix(Fpxm16,px+qx,py+qy);
      pix2 = PXMpix(Fpxm16,px-qx,py-qy);
      red = f65k * abs(pix1[0] - pix2[0]);
      green = f65k * abs(pix1[1] - pix2[1]);
      blue = f65k * abs(pix1[2] - pix2[2]);
      contrast = (1.0 - red) * (1.0 - green) * (1.0 - blue);
      contrast = 1.0 - contrast;
      if (contrast > maxcontrast) maxcontrast = contrast;
   }

   return maxcontrast;
}
