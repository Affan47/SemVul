humminbird_write_waypoint_wrapper(const waypoint* wpt)
{
  char* key;
  waypoint* tmpwpt;

  xasprintf(&key, "%s\01%.9f\01%.9f", wpt->shortname, wpt->latitude, wpt->longitude);

  if (! avltree_find(waypoints, key, (const void**)&tmpwpt)) {
    tmpwpt = (waypoint*)wpt;

    avltree_insert(waypoints, key, wpt);

    tmpwpt->extra_data = gb_int2ptr(waypoint_num + 1);
    humminbird_write_waypoint(wpt);
  } else {
    void* p = tmpwpt->extra_data;
    tmpwpt = (waypoint*)wpt;
    tmpwpt->extra_data = p;
  }

  xfree(key);
}
