drawNextField( bool signalOnCompletion )
{
   if ( !init() )
      return;

   if ( x == map.xsize ) {
      x = 0;
      ++y;
   }
   if ( y < map.ysize ) {
      if ( !updateField( MapCoordinate(x,y)))
         return;

      ++x;
   }
   if ( y == map.ysize ) {
      completed = true;
      if ( signalOnCompletion )
         generationComplete();

      completedMapImage = overviewMapImage.Duplicate();
      secondMapReady = true;
   }
}
