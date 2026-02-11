find_matching_waypoint(const char *name)
{
	Assert(name != NULL);
	SCP_list<waypoint_list>::iterator ii;

	for (ii = Waypoint_lists.begin(); ii != Waypoint_lists.end(); ++ii)
	{
		uint len = strlen(ii->get_name());


		if (!strnicmp(ii->get_name(), name, len))
		{

			if (*(name + len) != ':')
				continue;


			const char *index_str = name + len + 1;
			if (*index_str == '\0')
			{
				nprintf(("waypoints", "possible error with waypoint name '%s': no waypoint number after the colon\n", name));
				continue;
			}


			bool valid = true;
			for (const char *ch = index_str; *ch != '\0'; ch++)
			{
				if (!isdigit(*ch))
				{
					valid = false;
					break;
				}
			}
			if (!valid)
			{
				nprintf(("waypoints", "possible error with waypoint name '%s': string after the colon is not a number\n", name));
				continue;
			}


			uint index = atoi(index_str);
			if (index < 1 || index > ii->get_waypoints().size())
			{
				nprintf(("waypoints", "possible error with waypoint name '%s': waypoint number is out of range\n", name));
				continue;
			}

			return find_waypoint_at_index(&(*ii), index - 1);
		}
	}

	return NULL;
}
