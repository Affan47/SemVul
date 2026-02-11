fieldvisiblenow( const MapField* pe, Vehicle* veh, int player )
{
   GameMap* gamemap = pe->getMap();
   if ( player == -1 )
      return true;

   if ( player < -1 )
      return false;

   if ( !gamemap )
      return false;

   if ( pe ) {
      int c = (pe->visible >> ( player * 2)) & 3;

      if ( c < gamemap->getInitialMapVisibility( player ) )
         c = gamemap->getInitialMapVisibility( player );

      if (c > visible_ago) {
         if ( !veh )
            veh = pe->vehicle;

         if ( veh ) {
            if ((c == visible_all) || (veh->color / 8 == player ) || ((veh->height >= chschwimmend) && (veh->height <= chhochfliegend)))
               return true;
         }
         else
            if (pe->building != NULL) {
            if ((c == visible_all) || (pe->building->typ->height >= chschwimmend) || (pe->building->color == player*8))
               return true;
            }
            else
               return true;
      }
   }
   return false;
}
