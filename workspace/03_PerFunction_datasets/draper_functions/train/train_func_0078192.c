getProductionCost( const BuildingType* bld ) const
{
   int mf = getMap()->getgameparameter ( cgp_building_material_factor );
   int ff = getMap()->getgameparameter ( cgp_building_fuel_factor );

   if ( !mf )
      mf = 100;
   if ( !ff )
      ff = 100;

   return Resources( 0, bld->productionCost.material * mf / 100, bld->productionCost.fuel * ff / 100 );
}
