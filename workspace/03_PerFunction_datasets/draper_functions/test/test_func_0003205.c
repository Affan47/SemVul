ay_irc_got_welcome(const char *nick, const char *message,
	irc_message_prefix *prefix, irc_account *ia)
{
	Conversation *ecr = NULL;
	char room_name[BUF_LEN];
	eb_local_account *ela = (eb_local_account *)ia->data;

	snprintf(room_name, sizeof(room_name), "#notices-%s-%s@%s", ia->nick,
		ia->connect_address, ia->connect_address);

	if (!(ecr = ay_conversation_find_by_name(ela, room_name)))
		ecr = ay_irc_start_conversation(room_name, ela, FALSE, FALSE,
			FALSE);

	ay_conversation_display_notification(ecr, message, IRC_WELCOME);

	if (!strcmp(nick, ia->nick))
		return;


	if (ia->nick)
		free(ia->nick);

	ia->nick = strdup(nick);
}
