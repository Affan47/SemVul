gfire_proto_buddy_list(gfire_data *p_gfire, guint16 p_packet_len)
{
	if(!p_gfire)
		return;

	guint32 offset;
	gfire_buddy *gf_buddy = NULL;
	GList *friends = NULL;
	GList *nicks = NULL;
	GList *userids = NULL;
	GList *f, *n, *u;

	if (p_packet_len < 16)
	{
		purple_debug_error("gfire", "buddy list received, but too short. (%d bytes)\n", p_packet_len);
		return;
	}

	offset = XFIRE_HEADER_LEN;

	offset = gfire_proto_read_attr_list_ss(p_gfire->buff_in, &friends, "friends", offset);

	if(offset == -1 || !friends)
	{
		purple_debug_error("gfire", "empty list or error!\n");
		return;
	}

	offset = gfire_proto_read_attr_list_ss(p_gfire->buff_in, &nicks, "nick", offset);

	if(offset == -1)
	{
		purple_debug_error("gfire", "empty list or error!\n");
		g_list_free(friends);
		return;
	}

	offset = gfire_proto_read_attr_list_ss(p_gfire->buff_in, &userids, "userid", offset);

	if(offset == -1)
	{
		purple_debug_error("gfire", "empty list or error!\n");
		g_list_free(friends);
		g_list_free(nicks);
		return;
	}

	f = friends;
	n = nicks;
	u = userids;

	for(; f; f = g_list_next(f))
	{
		gf_buddy = gfire_find_buddy(p_gfire, f->data, GFFB_NAME);
		if(!gf_buddy)
		{
			gf_buddy = gfire_buddy_create(*(guint32*)u->data, (gchar*)f->data, (gchar*)n->data, GFBT_FRIEND);
			if(gf_buddy)
			{

				gfire_group *group = gfire_find_group(p_gfire, u->data, GFFG_BUDDY);
				gfire_add_buddy(p_gfire, gf_buddy, group);
			}
		}
		else if(!gfire_buddy_is_friend(gf_buddy))
		{

			gfire_group *group = gfire_find_group(p_gfire, u->data, GFFG_BUDDY);
			gfire_buddy_make_friend(gf_buddy, group);
			gfire_buddy_set_alias(gf_buddy, (gchar*)n->data);
		}

		g_free(f->data);
		g_free(u->data);
		g_free(n->data);

		u = g_list_next(u);
		n = g_list_next(n);
	}

	g_list_free(friends);
	g_list_free(nicks);
	g_list_free(userids);
}
