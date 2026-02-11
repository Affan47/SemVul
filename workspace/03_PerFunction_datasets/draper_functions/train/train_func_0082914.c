setServiceUnit ( Vehicle* veh )
{
   if ( veh )
      serviceUnitID = veh->networkid;
   else
      serviceUnitID = 0;
}
