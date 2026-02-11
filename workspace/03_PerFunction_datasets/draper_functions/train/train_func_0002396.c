runTextIO ( PropertyContainer& pc )
{
   pc.addTagInteger( "Mode", mode, entranceModeNum, entranceModes );
   pc.addTagInteger( "UnitHeightAbs", height_abs, choehenstufennum, heightTags );
   pc.addInteger( "UnitHeightRel", height_rel, -100 );
   pc.addTagInteger( "ContainerHeight", container_height, choehenstufennum, heightTags );
   pc.addTagInteger( "CategoriesNOT", vehicleCategoriesLoadable, cmovemalitypenum, unitCategoryTags, true );
   pc.addTagInteger( "DockingHeightAbs", dockingHeight_abs, choehenstufennum, heightTags, 0 );
   pc.addInteger( "DockingHeightRel", dockingHeight_rel, -100 );
   if ( pc.find( "RequireUnitFunction" )) {
      int r = 0;
      pc.addTagInteger( "RequireUnitFunction", r, VehicleType::legacyVehicleFunctionNum, vehicleAbilities, 0 );
      requiresUnitFeature = VehicleType::convertOldFunctions(r, pc.getFileName() );
   } else
      if ( pc.find( "RequiresUnitFeature" ) || !pc.isReading() )
         pc.addTagArray( "RequiresUnitFeature", requiresUnitFeature, ContainerBaseType::functionNum, containerFunctionTags );
      else
         requiresUnitFeature.reset();

   pc.addBool( "DisableAttack", disableAttack, false );
   pc.addInteger( "MoveCost", movecost, -1 );
   if ( movecost < 10 && movecost >= 0 )
      fatalError ( "MoveCost for TransportationIO is lower than 10! file: " + pc.getFileName() );
}
