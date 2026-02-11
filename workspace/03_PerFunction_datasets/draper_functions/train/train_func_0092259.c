WarpL_dialog_event(zdialog * zd, cchar *event)
{
   int         px, py, ii;
   float       wdx, wdy, wdw, wdh;
   int         fpx, fpy, epx, epy, vstat;
   double      scale, dispx, dispy;
   uint16      vpix[3], *pix3;

   if (zd->zstat) goto complete;

   if (strEqu(event,"undolast"))
   {
      if (NWarpL == 1) event = "undoall";
      else if (NWarpL) {
         ii = --NWarpL;
         wdx = WarpLmem[0][ii];
         wdy = WarpLmem[1][ii];
         wdw = WarpLmem[2][ii];
         wdh = WarpLmem[3][ii];
         WarpL_warpfunc(wdx,wdy,-wdw,-wdh,0);
         WarpL_warpfunc(wdx,wdy,-wdw,-wdh,1);
      }
   }

   if (strEqu(event,"undoall"))
   {
      NWarpL = 0;

      for (py = 0; py < E3hh; py++)
      for (px = 0; px < E3ww; px++)
      {
         ii = py * E3ww + px;
         WarpLx[ii] = WarpLy[ii] = 0.0;
      }
      edit_reset();
   }

   if (strEqu(event,"grid")) m_gridlines(0,0);

   if (strstr("KB G KB g",event))
      toggle_grid(2);

   return 1;

complete:

   save_grid(warpL_grid);
   Fgrid = 0;

   if (zd->zstat != 1) edit_cancel(EFwarpL);
   else if (NWarpL == 0) edit_cancel(EFwarpL);
   else
   {
      edit_fullsize();

      scale = 1.0 * (E3ww + E3hh) / (WarpLww + WarpLhh);

      for (fpy = 0; fpy < E3hh; fpy++)
      for (fpx = 0; fpx < E3ww; fpx++)
      {
         epx = WarpLww * fpx / E3ww;
         epy = WarpLhh * fpy / E3hh;
         ii = epy * WarpLww + epx;
         dispx = WarpLx[ii] * scale;
         dispy = WarpLy[ii] * scale;

         vstat = vpixel(E1pxm16,fpx+dispx,fpy+dispy,vpix);
         pix3 = PXMpix(E3pxm16,fpx,fpy);
         if (vstat) {
            pix3[0] = vpix[0];
            pix3[1] = vpix[1];
            pix3[2] = vpix[2];
         }
         else pix3[0] = pix3[1] = pix3[2] = 0;
      }

      edit_done(EFwarpL);
   }

   zfree(WarpLx);
   zfree(WarpLy);
   return 0;
}
