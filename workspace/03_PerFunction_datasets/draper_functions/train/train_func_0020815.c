getState( int player )
{
  Vehicle* veh = gamemap->getUnit( unitID );
  if ( !veh )
     return finally_fulfilled;
  if ( veh->getOwner() != player )
     return fulfilled;
  return unfulfilled;
}
