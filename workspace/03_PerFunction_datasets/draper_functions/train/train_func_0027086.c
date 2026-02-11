gfire_purple_add_buddy_msg_ok_cb(PurpleBuddy *p_buddy, const gchar *p_msg)
{
	PurpleConnection *gc = purple_account_get_connection(purple_buddy_get_account(p_buddy));
	if(!gc)
		return;


	guint16 packet_len = gfire_proto_create_invitation(purple_buddy_get_name(p_buddy), p_msg ? p_msg : "");
	if(packet_len > 0) gfire_send(gc, packet_len);
}
