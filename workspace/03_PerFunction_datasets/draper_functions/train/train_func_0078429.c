WarpA_warpfunc(float wdx, float wdy, float wdw, float wdh, int acc)
{
   int            ii, px, py, ww, hh, vstat;
   double         ddx, ddy, dpe, dpm, mag, dispx, dispy;
   uint16         vpix[3], *pix3;

   edit_zapredo();

   if (! Factivearea) return;

   for (py = sa_miny; py < sa_maxy; py++)
   for (px = sa_minx; px < sa_maxx; px++)
   {
      ii = py * Fww + px;
      dpe = sa_pixmap[ii];
      if (dpe < 1) continue;
      dpe -= 1;

      ddx = (px - wdx);
      ddy = (py - wdy);
      dpm = sqrt(ddx*ddx + ddy*ddy);

      mag = (dpe / (dpm + dpe)) * (1.0 - dpm / (dpm + dpe));

      dispx = -wdw * mag;
      dispy = -wdh * mag;

      if (acc) {
         WarpAx[ii] += dispx;
         WarpAy[ii] += dispy;
         continue;
      }

      dispx += WarpAx[ii];
      dispy += WarpAy[ii];

      vstat = vpixel(E1pxm16,px+dispx,py+dispy,vpix);
      if (vstat) {
         pix3 = PXMpix(E3pxm16,px,py);
         pix3[0] = vpix[0];
         pix3[1] = vpix[1];
         pix3[2] = vpix[2];
      }
   }

   ww = sa_maxx - sa_minx;
   hh = sa_maxy - sa_miny;
   mwpaint3(sa_minx,sa_miny,ww,hh);

   CEF->Fmod = 1;
   return;
}
