print_addgrid(PXM *printimage)
{
   PXM      *temp8;
   uint8    *pixel;
   int      px, py, ww, hh, row;
   int      startx, starty, stepx, stepy;

   if (! Fgrid) return 0;

   temp8 = f_load(curr_file,8);
   if (! temp8) return 0;

   ww = temp8->ww;
   hh = temp8->hh;
   row = ww * 3;

   stepx = gridspace[0];
   stepy = gridspace[1];

   stepx = stepx / Mscale;
   stepy = stepy / Mscale;

   if (gridcount[0]) stepx = ww / (1 + gridcount[0]);
   if (gridcount[1]) stepy = hh / ( 1 + gridcount[1]);

   startx = stepx * gridoffset[0] / 100;
   if (startx < 0) startx += stepx;

   starty = stepy * gridoffset[1] / 100;
   if (starty < 0) starty += stepy;

   if (gridon[0]) {
      for (px = startx; px < ww-1; px += stepx)
      for (py = 0; py < hh; py++)
      {
         pixel = PXMpix8(temp8,px,py);
         pixel[0] = pixel[1] = pixel[2] = 255;
         pixel[3] = pixel[4] = pixel[5] = 0;
      }
   }

   if (gridon[1]) {
      for (py = starty; py < hh-1; py += stepy)
      for (px = 0; px < ww; px++)
      {
         pixel = PXMpix8(temp8,px,py);
         pixel[0] = pixel[1] = pixel[2] = 255;
         pixel[row] = pixel[row+1] = pixel[row+2] = 0;
      }
   }

   return temp8;
}
