sa_geom_mousefunc()
{
   static int  mx1, my1, mx2, my2;
   static int  mdx0, mdy0;

   if (sa_stat != 1) return;

   if (sa_currseq > sa_maxseq-2) {
      zmessageACK(mWin,ZTX("exceed %d edits"),sa_maxseq);
      return;
   }

   if (RMclick)
   {
      RMclick = 0;
      sa_unselect_pixels();
      sa_geom1 = sa_geom2 = 0;
      mwpaint2();
      return;
   }

   if (! Mxdrag && ! Mydrag) return;

   if (Mxdown != mdx0 || Mydown != mdy0) {
      mdx0 = Mxdown;
      mdy0 = Mydown;
      mx1 = mdx0;
      my1 = mdy0;
      sa_geom1 = 1;
      sa_geom2 = 0;
      return;
   }

   if (sa_geom2) sa_unselect_pixels();
   mx2 = Mxdrag;
   my2 = Mydrag;
   sa_geom2 = 1;

   sa_nextseq();

   if (sa_mode == 1)
   {
      sa_draw_line(mx1,my1,mx2,my1);
      sa_draw_line(mx2,my1,mx2,my2);
      sa_draw_line(mx2,my2,mx1,my2);
      sa_draw_line(mx1,my2,mx1,my1);
   }

   if (sa_mode == 2)
   {
      double   a, b, a2, b2;
      double   x, y, x2, y2, cx, cy;
      int      px, py;

      a = abs(mx2 - mx1);
      b = abs(my2 - my1);
      a2 = a * a;
      b2 = b * b;
      cx = mx1;
      cy = my1;

      for (y = -b; y < b; y++)
      {
         y2 = y * y;
         x2 = a2 * (1 - y2 / b2);
         x = sqrt(x2);
         py = y + cy;
         px = cx - x + 0.5;
         sa_draw1pix(px,py);
         px = cx + x + 0.5;
         sa_draw1pix(px,py);
      }

      for (x = -a; x < a; x++)
      {
         x2 = x * x;
         y2 = b2 * (1 - x2 / a2);
         y = sqrt(y2);
         px = cx + x;
         py = cy - y + 0.5;
         sa_draw1pix(px,py);
         py = cy + y + 0.5;
         sa_draw1pix(px,py);
      }
   }

   mwpaint2();
   return;
}
