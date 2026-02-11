skype_remove_buddy(PurpleConnection *gc, PurpleBuddy *buddy, PurpleGroup *group)
{

	GSList *buddies, *current;
	PurpleBuddy *otherbuddy;
	PurpleGroup *othergroup;
	int group_number;

	buddies = purple_find_buddies(buddy->account, buddy->name);
	if (buddies == NULL)
		return;

	for(current = buddies; current; current = g_slist_next(current))
	{
		otherbuddy = current->data;
		if (otherbuddy == NULL)
			continue;
		othergroup = purple_buddy_get_group(otherbuddy);
		if (othergroup == NULL)
			continue;
		if (!g_str_equal(othergroup->name, group->name))
		{

			group_number = skype_find_group_with_name(group->name);
			if (group_number)
				skype_send_message_nowait("ALTER GROUP %d REMOVEUSER %s", group_number, buddy->name);
			g_slist_free(buddies);
			return;
		}
	}
	g_slist_free(buddies);


	skype_send_message_nowait("SET USER %s BUDDYSTATUS 1", buddy->name);
}
