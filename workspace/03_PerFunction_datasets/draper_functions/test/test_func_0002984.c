ss_venetian()
{
   int         py1, py2;
   uint8       *pix3;
   int         louver, Nlouvers = 20;
   int         louversize = ss_hh / Nlouvers;
   double      delay = 1.0 / louversize;

   for (py1 = 0; py1 < louversize; py1++)
   {
      for (louver = 0; louver < Nlouvers; louver++)
      {
         py2 = py1 + louver * louversize;
         if (py2 >= ss_hh) break;
         pix3 = PXMpix8(ss_pxmnew,0,py2);
         gdk_draw_rgb_image(drWin->window, gdkgc, 0, py2, ss_ww, 1, NODITHER, pix3, ss_ww*3);
      }

      zsleep(delay);
   }

   pix3 = PXMpix8(ss_pxmnew,0,0);
   gdk_draw_rgb_image(drWin->window, gdkgc, 0, 0, ss_ww, ss_hh, NODITHER, pix3, ss_ww * 3);
   return;
}
