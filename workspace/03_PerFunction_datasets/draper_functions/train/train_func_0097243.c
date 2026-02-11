evaluateProduction( const ContainerBaseType* potentialFactory, const VehicleType* vt, GameMap* gamemap )
{
   if ( potentialFactory->vehicleFit( vt ) && potentialFactory->hasFunction( ContainerBaseType::InternalVehicleProduction)) {
      if ( potentialFactory->vehicleCategoriesProduceable & (1 << vt->movemalustyp))
         for ( int h = 0; h < 8; ++h )
            if ( potentialFactory->height & (1<<h))
               if ( potentialFactory->vehicleUnloadable(vt,h) || potentialFactory->hasFunction( ContainerBaseType::ProduceNonLeavableUnits ))
                  if ( !potentialFactory->hasFunction( ContainerBaseType::NoProductionCustomization) || factoryProductionInstanceExists( potentialFactory, vt, gamemap ))
                     return 1;
   }

   return 0;
}
