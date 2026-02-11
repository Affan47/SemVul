searchfield ( int x, int y, int dir )
{
  int s;

   MapField* fld = actmap->getField ( x, y );
   if ( !fld )
      return;

   int arr[sidenum];

   do {

      if ( fld->a.temp )
         return;

      #ifdef netdebug
      cursor.gotoxy ( a, b );
      displaymap();
      #endif

      if ( fld->building ) {
         searchbuilding ( x, y );
         return;
      }

      fld->a.temp = 1;

      int d = fieldavail( x, y );
      if ( d <= 0 )
         return;

      searchvehicle ( x, y );

      int olddir = dir + sidenum/2;
      while (olddir >= sidenum )
         olddir -= sidenum;

         int r = 0;
         for (s = 0; s < sidenum; s++) {
            if ( (d & (1 << s))  &&  ( s != olddir )) {
               arr[ r ] = s;
               r++;
            }
         }


         if (r > 1) {
            for ( s = 0; s < r; s++) {
               int nx = x;
               int ny = y;
               getnextfield ( nx, ny, arr[s] );
               searchfield( nx, ny, arr[s] );
               if ( searchfinished() )
                  return ;
            }
            return;
         } else
            if ( r == 1 ) {
               dir = arr[0];
               getnextfield ( x, y, dir );
               fld = actmap->getField( x, y );
               if ( !fld )
                  return;
            } else
               return;
   }  while ( 1 );

}
