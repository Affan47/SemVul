free_waypoints(waypoint** waypts)
{
  waypoint** wayptp;

  for (wayptp = waypts; wayptp < waypts + MAX_WAYPOINTS; wayptp++) {
    if (*wayptp) {
      waypt_free(*wayptp);
    }
  }

  xfree(waypts);
}
