showUnitEndurance()
{

   vector<VehicleType*> units;
   for ( int i = 0; i < vehicleTypeRepository.getNum(); ++i ) {
      VehicleType* vt = vehicleTypeRepository.getObject_byPos(i);
      if ( vt && (vt->movemalustyp == MoveMalusType::medium_aircraft ||
           vt->movemalustyp == MoveMalusType::light_aircraft  ||
           vt->movemalustyp == MoveMalusType::heavy_aircraft  ||
           vt->movemalustyp == MoveMalusType::helicopter))
         units.push_back( vt );
   }
   sort( units.begin(), units.end(), vehicleComp );

   ASCString s;
   for ( vector<VehicleType*>::iterator i = units.begin(); i != units.end(); ++i )
   {
      ASCString u;
      ASCString range;
      if ( (*i)->fuelConsumption )
         range = ASCString::toString( (*i)->getStorageCapacity(0).fuel / (*i)->fuelConsumption);
      else
         range = "-";

      u.format( "#vehicletype=%d# %s : %d fuel ; %s fields range ; %d turns endurance \n", (*i)->id, (*i)->getName().c_str(), (*i)->getStorageCapacity(0).fuel, range.c_str(), UnitHooveringLogic::getEndurance(*i) );
      s += u;
   }

   ViewFormattedText vft("Unit Endurance", s, PG_Rect( -1, -1, 650, 550 ));
   vft.Show();
   vft.RunModal();
}
