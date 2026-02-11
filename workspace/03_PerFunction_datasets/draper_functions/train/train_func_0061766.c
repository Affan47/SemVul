removeUnitFromCargo( int nwid, bool recursive )
{
   for ( Cargo::iterator i = cargo.begin(); i != cargo.end(); ++i )
      if ( *i ) {
         if ( (*i)->networkid == nwid ) {
            (*i)->cargoParent = NULL;
            *i = NULL;

            if ( cargo.size() > baseType->maxLoadableUnits ) {


               compactCargo();
            }

            cargoChanged();
            return true;
         }
         if ( recursive )
            if ( (*i)->removeUnitFromCargo( nwid, recursive ))
               return true;
      }

   return false;
}
