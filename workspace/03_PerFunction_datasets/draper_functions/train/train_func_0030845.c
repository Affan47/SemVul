find_index_of_waypoint(waypoint_list *wp_list, waypoint *wpt)
{
	Assert(wp_list != NULL);
	Assert(wpt != NULL);
	SCP_list<waypoint>::iterator ii;

	int index = 0;
	for (ii = wp_list->get_waypoints().begin(); ii != wp_list->get_waypoints().end(); ++ii)
	{
		if (&(*ii) == wpt)
			return index;
		index++;
	}

	return -1;
}
