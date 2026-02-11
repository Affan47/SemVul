run ( int x, int y)
{
   initsearch ( MapCoordinate(x, y), 1 , 2 );
   startsearch();
   if ( ownFields[1] && !enemyFields[1] ) {
      if ( enemyFields[2] > ownFields[2] )
         return 0;
      else
         if ( enemyFields[2] )
            return 1;
   }
   return -1;
}
