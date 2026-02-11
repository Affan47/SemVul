getInstances( const ContainerBaseType* evaluatedFactory, const VehicleType* unitsToProduce, GameMap* gamemap, bool lineAvail )
{
   ASCString instances;
   if ( lineAvail ) {
      int count = 0;
      ASCString units = evaluatedFactory->getName() + ": ";

      for ( Player::VehicleList::const_iterator j = gamemap->getCurrentPlayer().vehicleList.begin(); j != gamemap->getCurrentPlayer().vehicleList.end(); ++j )
         if ( (*j)->typ == evaluatedFactory )
            for ( Vehicle::Production::const_iterator i = (*j)->getProduction().begin(); i != (*j)->getProduction().end(); ++i)
               if ( *i == unitsToProduce ) {
                  units += (*j)->getPosition().toString();
                  ++count;
               }

      if ( count )
         instances += units + "\n";

   }
   {
      int count = 0;
      ASCString units = evaluatedFactory->getName() + ": ";

      for ( Player::BuildingList::const_iterator j = gamemap->getCurrentPlayer().buildingList.begin(); j != gamemap->getCurrentPlayer().buildingList.end(); ++j )
         if ( (*j)->typ == evaluatedFactory ) {
            if ( lineAvail ) {
               for ( ContainerBase::Production::const_iterator k = (*j)->getProduction().begin(); k != (*j)->getProduction().end(); ++k )
                  if ( *k == unitsToProduce ) {
                     units += (*j)->getPosition().toString();
                     ++count;
                  }
            } else {
               if ( unitsToProduce->techDependency.available( gamemap->getCurrentPlayer().research ) ) {
                  bool found = false;
                  for ( ContainerBase::Production::const_iterator k = (*j)->getProduction().begin(); k != (*j)->getProduction().end(); ++k )
                     if ( *k == unitsToProduce )
                        found = true;

                  if ( !found ) {
                     units += (*j)->getPosition().toString();
                     ++count;
                  }
               }
            }
         }
      if ( count )
         instances += units + "\n";
   }

   return instances;
}
