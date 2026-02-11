ay_irc_leave_chat_room(Conversation *room)
{
	char room_name[BUF_LEN];

	irc_local_account *ila =
		(irc_local_account *)room->local_user->
		protocol_local_account_data;

	if (!room->local_user->connected)
		return;


	snprintf(room_name, sizeof(room_name), "#notices-%s-%s@%s", ila->ia->nick,
		 ila->ia->connect_address, ila->ia->connect_address);

	if (strcasecmp(room->name, room_name))
		irc_leave_chat_room(room->name, ila->ia);

	ila->current_rooms = l_list_remove(ila->current_rooms, room);
}
