ay_oscar_decline_invite(eb_local_account *account, void *data)
{
	struct oscar_chat_room_data *ocrd = (struct oscar_chat_room_data *)data;
	LOG(("ay_oscar_decline_invite()"))
		g_free(ocrd->name);
	g_free(ocrd);
}
