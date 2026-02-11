getLocalCoordinate( const MapCoordinate& entryOnMap, const MapCoordinate& field ) const
{
   int homex = entryOnMap.x - entry.x;
   int homey = entryOnMap.y - entry.y;

   if ( (entry.y & 1) && !(entryOnMap.y & 1))
      homex -= 1;


   int ly = field.y - homey;
   int lx = field.x - homex;
   if ( (ly & 1) && (homey & 1 ))
      lx -= 1;

   if ( lx >= 0 && lx < 4 && ly >= 0 && ly < 6 && fieldExists(LocalCoordinate(lx,ly)))
      return LocalCoordinate(lx,ly);
   else
      return LocalCoordinate();
}
