find_update_path(List *evi_list,
				 ExtensionVersionInfo *evi_start,
				 ExtensionVersionInfo *evi_target,
				 bool reinitialize)
{
	List	   *result;
	ExtensionVersionInfo *evi;
	ListCell   *lc;


	Assert(evi_start != evi_target);

	if (reinitialize)
	{
		foreach(lc, evi_list)
		{
			evi = (ExtensionVersionInfo *) lfirst(lc);
			evi->distance_known = false;
			evi->distance = INT_MAX;
			evi->previous = NULL;
		}
	}

	evi_start->distance = 0;

	while ((evi = get_nearest_unprocessed_vertex(evi_list)) != NULL)
	{
		if (evi->distance == INT_MAX)
			break;
		evi->distance_known = true;
		if (evi == evi_target)
			break;
		foreach(lc, evi->reachable)
		{
			ExtensionVersionInfo *evi2 = (ExtensionVersionInfo *) lfirst(lc);
			int			newdist;

			newdist = evi->distance + 1;
			if (newdist < evi2->distance)
			{
				evi2->distance = newdist;
				evi2->previous = evi;
			}
			else if (newdist == evi2->distance &&
					 evi2->previous != NULL &&
					 strcmp(evi->name, evi2->previous->name) < 0)
			{


				evi2->previous = evi;
			}
		}
	}


	if (!evi_target->distance_known)
		return NIL;


	result = NIL;
	for (evi = evi_target; evi != evi_start; evi = evi->previous)
		result = lcons(evi->name, result);

	return result;
}
