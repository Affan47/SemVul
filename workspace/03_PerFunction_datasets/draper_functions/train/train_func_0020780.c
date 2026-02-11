reset(GameMap& map)
{
   if ( veh && veh->getMap() == &map )
      veh = NULL;

   if ( bld && bld->getMap() == &map )
      bld = NULL;
}
