find ( const MapCoordinate3D& pos )
{
   for ( iterator i = begin(); i != end(); i++ )
      if ( i->h == pos )
         return i;
   return end();
}
