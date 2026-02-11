find_waypoint_list_at_index(int index)
{
	Assert(index >= 0);

	int i = 0;
	SCP_list<waypoint_list>::iterator ii;

	for (ii = Waypoint_lists.begin(); ii != Waypoint_lists.end(); ++i, ++ii)
	{
		if (i == index)
			return &(*ii);
	}

	return NULL;
}
