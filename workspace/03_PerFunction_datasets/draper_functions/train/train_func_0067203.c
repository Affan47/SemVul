gfire_chat_proto_accessibility_change(gfire_data *p_gfire, guint16 p_packet_len)
{
	if(!p_gfire)
		return;

	guint32 offset = XFIRE_HEADER_LEN;

	guint8 *chat_id = NULL;
	gfire_chat *chat = NULL;
	guint32 access = 0;

	offset = gfire_proto_read_attr_chatid_bs(p_gfire->buff_in, &chat_id, 0x04, offset);
	if(offset == -1 || !chat_id)
		return;

	chat = gfire_find_chat(p_gfire, chat_id, GFFC_CID);
	if(!chat)
	{
		g_free(chat_id);
		purple_debug_error("gfire", "gfire_chat_proto_accessibility_change: Unknown chat id!\n");
		return;
	}

	g_free(chat_id);

	offset = gfire_proto_read_attr_int32_bs(p_gfire->buff_in, &access, 0x17, offset);
	if(offset == -1)
		return;

	gfire_chat_set_accessibility(chat, access, TRUE);
}
