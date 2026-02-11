gfire_chat_proto_user_join(gfire_data *p_gfire, guint16 p_packet_len)
{
	if(!p_gfire)
		return;

	guint32 offset = XFIRE_HEADER_LEN;

	guint8 *chat_id = NULL;
	gfire_chat *chat = NULL;
	guint32 userid = 0;
	gchar *name = NULL;
	gchar *nick = NULL;
	guint32 perm = 0;
	gfire_buddy *gf_buddy = NULL;

	offset = gfire_proto_read_attr_chatid_bs(p_gfire->buff_in, &chat_id, 0x04, offset);
	if(offset == -1 || !chat_id)
		return;

	chat = gfire_find_chat(p_gfire, chat_id, GFFC_CID);
	if(!chat)
	{
		g_free(chat_id);
		purple_debug_error("gfire", "gfire_chat_proto_user_leave: Unknown chat id!\n");
		return;
	}

	g_free(chat_id);

	offset = gfire_proto_read_attr_int32_bs(p_gfire->buff_in, &userid, 0x01, offset);
	if(offset == -1)
		return;

	offset = gfire_proto_read_attr_string_bs(p_gfire->buff_in, &name, 0x02, offset);
	if(offset == -1 || !name)
	{
		return;
	}

	offset = gfire_proto_read_attr_string_bs(p_gfire->buff_in, &nick, 0x0D, offset);
	if(offset == -1 || !nick)
	{
		g_free(name);
		return;
	}

	offset = gfire_proto_read_attr_int32_bs(p_gfire->buff_in, &perm, 0x12, offset);
	if(offset == -1)
		return;

	gf_buddy = gfire_buddy_create(userid, name, nick, GFBT_GROUPCHAT);
	gfire_chat_add_user(chat, gf_buddy, perm, TRUE);

	purple_debug(PURPLE_DEBUG_MISC, "gfire", "groupchat join, userid: %u, username: %s, alias: %s\n",
				 userid, NN(name), NN(nick));

	g_free(name);
	g_free(nick);
}
