gfire_proto_clan_list(gfire_data *p_gfire, guint16 p_packet_len)
{
	if(!p_gfire)
		return;

	guint32 offset = XFIRE_HEADER_LEN;

	GList *clanids = NULL;
	GList *clanLongNames = NULL;
	GList *clanShortNames = NULL;
	GList *clanTypes = NULL;
	gfire_clan *newClan = NULL;


	offset = gfire_proto_read_attr_list_bs(p_gfire->buff_in, &clanids, 0x6C, offset);
	if(offset == -1 || !clanids)
		return;

	offset = gfire_proto_read_attr_list_bs(p_gfire->buff_in, &clanLongNames, 0x02, offset);
	if(offset == -1 || !clanLongNames)
	{
		g_list_free(clanids);
		return;
	}

	offset = gfire_proto_read_attr_list_bs(p_gfire->buff_in, &clanShortNames, 0x72, offset);
	if(offset == -1 || !clanShortNames)
	{
		g_list_free(clanids);
		g_list_free(clanLongNames);
		return;
	}

	offset = gfire_proto_read_attr_list_bs(p_gfire->buff_in, &clanTypes, 0x34, offset);
	if(offset == -1 || !clanTypes)
	{
		g_list_free(clanids);
		g_list_free(clanLongNames);
		g_list_free(clanShortNames);
		return;
	}

	GList *id = clanids; GList *ln = clanLongNames; GList *sn = clanShortNames; GList *t = clanTypes;
	for(; id; id = g_list_next(id))
	{
		newClan = gfire_find_clan(p_gfire, *(guint32*)id->data);
		if(!newClan)
		{
			newClan = gfire_clan_create(*(guint32*)id->data, (const gchar*)ln->data, (const gchar*)sn->data, TRUE);
			if(newClan)
				gfire_add_clan(p_gfire, newClan);
		}
		else
			gfire_clan_set_names(newClan, (const gchar*)ln->data, (const gchar*)sn->data);

		g_free(id->data);
		g_free(ln->data);
		g_free(sn->data);
		g_free(t->data);

		ln = g_list_next(ln);
		sn = g_list_next(sn);
		t = g_list_next(t);
	}

	g_list_free(clanids);
	g_list_free(clanLongNames);
	g_list_free(clanShortNames);
	g_list_free(clanTypes);
}
