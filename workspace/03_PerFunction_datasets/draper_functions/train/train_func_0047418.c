skype_cb_real_name(PurpleConnection *gc, int id, const char *who)
{
	PurpleBuddy *buddy;
	SkypeBuddy *sbuddy;

	printf("CB Real name for %s in %d\n", who, id);

	buddy = purple_find_buddy(gc->account, who);
	if (buddy && buddy->alias)
	{
		return g_strdup(buddy->alias);
	} else if (buddy && buddy->server_alias)
	{
		return g_strdup(buddy->server_alias);
	} else if (buddy && buddy->proto_data)
	{
		sbuddy = buddy->proto_data;
		if (sbuddy->fullname)
			return g_strdup(sbuddy->fullname);
	}

	return NULL;
}
