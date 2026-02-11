fieldReachable( const MapCoordinate& dest )
{
   MapField* fld = getMap()->getField( dest );
   if ( beeline( dest, getUnit()->getPosition()) <= getUnit()->typ->jumpDrive.maxDistance )
      if ( !fld->vehicle && !fld->building )
         if ( fieldvisiblenow( fld, getUnit()->getOwner() ))
            if ( getUnit()->typ->jumpDrive.targetterrain.accessible( fld->bdt ) > 0 )
               return true;

   return false;
}
