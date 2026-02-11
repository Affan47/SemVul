dist ( const MapCoordinate3D& a, const vector<MapCoordinate3D>& b )
{
   DistanceType d = longestPath;
   for ( vector<MapCoordinate3D>::const_iterator i = b.begin(); i != b.end(); i++ ) {
      DistanceType e = dist(a,*i);
      if ( maxVehicleSpeedFactor )
         e /= maxVehicleSpeedFactor;
      if ( d > e )
         d = e;
   }
   return d;
}
