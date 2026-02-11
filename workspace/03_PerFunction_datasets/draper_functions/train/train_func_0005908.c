unbend_mousefunc()
{
   cchar       *close;
   double      dist1, dist2;
   double      mpx = 0, mpy = 0;

   if (LMclick) {
      LMclick = 0;
      mpx = Mxclick;
      mpy = Myclick;
   }

   if (Mxdrag || Mydrag) {
      mpx = Mxdrag;
      mpy = Mydrag;
   }

   if (! mpx && ! mpy) return;

   mpx = 1.0 * mpx / E3ww;
   mpy = 1.0 * mpy / E3hh;

   if (mpx < 0.2 || mpx > 0.8 ) {
      if (mpy < 0.1 || mpy > 0.9) return;
   }
   else if (mpy < 0.2 || mpy > 0.8) {
      if (mpx < 0.1 || mpx > 0.9) return;
   }
   else return;

   close = "?";
   dist1 = 2;

   dist2 = mpx * mpx + (mpy-unbend_y1) * (mpy-unbend_y1);
   if (dist2 < dist1) {
      dist1 = dist2;
      close = "left";
   }

   dist2 = (1-mpx) * (1-mpx) + (mpy-unbend_y2) * (mpy-unbend_y2);
   if (dist2 < dist1) {
      dist1 = dist2;
      close = "right";
   }

   dist2 = (mpx-unbend_x1) * (mpx-unbend_x1) + mpy * mpy;
   if (dist2 < dist1) {
      dist1 = dist2;
      close = "top";
   }

   dist2 = (mpx-unbend_x2) * (mpx-unbend_x2) + (1-mpy) * (1-mpy);
   if (dist2 < dist1) {
      dist1 = dist2;
      close = "bottom";
   }

   if (strEqu(close,"left")) unbend_y1 = mpy;
   if (strEqu(close,"right")) unbend_y2 = mpy;
   if (strEqu(close,"top")) unbend_x1 = mpx;
   if (strEqu(close,"bottom")) unbend_x2 = mpx;

   signal_thread();

   return;
}
