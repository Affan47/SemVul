placeUnit( GameMap* map, const MapCoordinate& pos, const VehicleType* veh, int owner )
{
   if ( map && veh && owner >= 0 && owner < 8 ) {
      MapField* fld = map->getField(pos);
      if ( fld ) {
         int r = VehicleItem::place( map, pos, veh, owner );
         if ( r < 0 )
            return NULL;
         else
            return fld->vehicle;
      }
   }
   return NULL;
}
