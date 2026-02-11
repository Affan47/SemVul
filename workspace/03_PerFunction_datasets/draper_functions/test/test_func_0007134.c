setDestination( const MapCoordinate& destination )
{
   if ( getState() != Evaluated )
      searchFields();

   bool found = false;
   for ( set<MapCoordinate3D>::iterator i = reachableFields.begin(); i != reachableFields.end(); ++i )
      if ( destination.x == i->x && destination.y == i->y ) {
         this->destination = *i;
         found = true;
         multiTurnMovement = false;
         break;
      }

   if ( !found ) {

      MapField* fld  = getMap()->getField( destination );
      if ( !fld )
         return;

      if ( fld->getContainer() )
         this->destination.setnum( destination.x, destination.y, -1 );
      else
          this->destination = MapCoordinate3D( destination, getUnit()->getHeight() );


      multiTurnMovement = true;
   }

   setState( SetUp );
}
