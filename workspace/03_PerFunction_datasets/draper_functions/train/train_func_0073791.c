evaluate( TechnologyPresenter::Gadgets& storage )
      {
         for ( int i=0; i < vehicleTypeRepository.getNum() ; i++ ) {
            const VehicleType* v = vehicleTypeRepository.getObject_byPos ( i );
            if ( !v->techDependency.available( p.research ))
               units.remove( v );
         }

         for ( int i=0; i < buildingTypeRepository.getNum() ; i++ ) {
            const BuildingType* b = buildingTypeRepository.getObject_byPos ( i );
            if ( !b->techDependency.available( p.research ))
               buildings.remove( b );
         }

         storage.buildings = buildings;
         storage.units = units;
      }
}
