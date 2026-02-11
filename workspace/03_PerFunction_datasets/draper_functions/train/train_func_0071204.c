beginTurn()
{


   if ( getCarrier() ) {
      int mx = -1;
      int newHeight = height;
      for ( int h = 0; h < 8; h++ )
         if ( typ->height & ( 1 << h))
            if ( typ->movement[h] > mx ) {
               mx = typ->movement[h];
               newHeight = 1 << h;
            }

      if ( newHeight != height ) {
         height = newHeight;
      }
   }
   resetMovement();

}
