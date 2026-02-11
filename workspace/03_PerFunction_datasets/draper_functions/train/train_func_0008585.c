cim_curve_Vimage(int im)
{
   int         px, py, ww, hh, vstat;
   double      ww2, hh2;
   double      dx, dy;
   double      F = lens_mm;
   double      S = 35.0;
   double      R1, R2, G, T, bow;
   PXM         *pxmin, *pxmout;
   uint16      vpix[3], *pix;

   pxmin = cimPXMs[im];
   ww = pxmin->ww;
   hh = pxmin->hh;
   ww2 = 0.5 * ww;
   hh2 = 0.5 * hh;

   if (hh > ww) S = S * ww / hh;
   F = F / S;
   S = ww2;
   F = F * ww;
   R1 = F;

   bow = -lens_bow * 0.01 / hh2 / hh2;
   if (hh > ww)
      bow = -lens_bow * 0.01 / ww2 / ww2;

   pxmout = PXM_make(ww,hh,16);

   for (py = 0; py < hh; py++)
   for (px = 0; px < ww; px++)
   {
      dx = px - ww2;
      dy = py - hh2;
      T = dy / R1;
      dy = F * tan(T);
      R2 = sqrt(dy * dy + F * F);
      G = R1 - R2;
      dx = (dx * R2) / (R2 + G);
      dy += bow * dy * dx * dx;
      dx += ww2;
      dy += hh2;
      vstat = vpixel(pxmin,dx,dy,vpix);
      pix = PXMpix(pxmout,px,py);
      if (vstat) {
         pix[0] = vpix[0];
         pix[1] = vpix[1];
         pix[2] = vpix[2];
      }
      else pix[0] = pix[1] = pix[2] = 0;
   }

   for (py = 1; py < hh2; py++) {
      pix = PXMpix(pxmout,ww/2,py);
      if (pix[2]) break;
   }
   cimShrink = py-1;

   PXM_free(pxmin);
   cimPXMs[im] = pxmout;

   return;
}
