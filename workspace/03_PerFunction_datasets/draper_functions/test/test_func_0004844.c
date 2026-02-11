fillline ( int x1, int x2 )
{
  if ( tvt_dispactive )
      if ( tvt_yp + activefontsettings.height > tvt_starty ) {
         int tvtny1 = tvt_y1 + tvt_yp - tvt_starty;
         int tvtny2 = tvt_y1 + tvt_yp - tvt_starty + tvt_maxlineheight;
         if (tvtny1 < tvt_y1) {
            tvtny1 =  tvt_y1;

         }
         if (tvtny2 > tvt_y2)
            tvtny2 =  tvt_y2;
         if (x2 > x1)
           if (tvtny2 > tvtny1)
              bar ( x1, tvtny1, x2, tvtny2, tvt_background);
      }
}
