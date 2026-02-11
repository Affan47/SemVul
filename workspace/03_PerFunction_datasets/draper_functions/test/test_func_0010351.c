place( const MapCoordinate& mc ) const
{
   MapField* fld = actmap->getField(mc);
   fld->typ = item->weather[0];
   fld->setWeather( selection.getWeather() );
   fld->setparams();
   for ( int d = 0; d < 6; ++d ) {
      MapCoordinate pos = getNeighbouringFieldCoordinate( mc, d );
      MapField* fld = actmap->getField( pos );
      if ( fld )
         for ( MapField::ObjectContainer::iterator i = fld->objects.begin(); i != fld->objects.end(); ++i )
            calculateobject( pos, false, i->typ, actmap );
   }
   return 0;
}
