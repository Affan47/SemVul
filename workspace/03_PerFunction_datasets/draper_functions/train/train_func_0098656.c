ss_loadimage(char *file, PXM *pxmout)
{
   int         cc, fww, fhh, px, py, orgx, orgy;
   PXM         *pxmtemp1, *pxmtemp2;
   double      wscale, hscale, scale;
   uint8       *pix1, *pix2;

   cc = ss_ww * ss_hh * 3;
   memset(pxmout->bmp,0,cc);

   pxmtemp1 = f_load(file,8);
   if (! pxmtemp1) return;

   fww = pxmtemp1->ww;
   fhh = pxmtemp1->hh;

   wscale = 1.0 * ss_ww / fww;
   hscale = 1.0 * ss_hh / fhh;
   if (wscale < hscale) scale = wscale;
   else  scale = hscale;
   fww = fww * scale;
   fhh = fhh * scale;

   pxmtemp2 = PXM_rescale(pxmtemp1,fww,fhh);

   orgx = 0.5 * (ss_ww - fww);
   orgy = 0.5 * (ss_hh - fhh);

   for (py = 0; py < fhh; py++)
   for (px = 0; px < fww; px++)
   {
      pix1 = PXMpix8(pxmtemp2,px,py);
      pix2 = PXMpix8(pxmout,px+orgx,py+orgy);
      pix2[0] = pix1[0];
      pix2[1] = pix1[1];
      pix2[2] = pix1[2];
   }

   PXM_free(pxmtemp1);
   PXM_free(pxmtemp2);

   return;
}
