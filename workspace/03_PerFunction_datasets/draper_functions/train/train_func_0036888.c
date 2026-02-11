ay_got_namereply(irc_name_list *list, const char *channel,
	irc_message_prefix *prefix, irc_account *ia)
{
	Conversation *ecr;
	eb_account *ea;
	eb_local_account *ela = (eb_local_account *)ia->data;
	ay_irc_account *eia;

	char buddy_name[BUF_LEN];

	if ((ecr = ay_conversation_find_by_name(ela, channel))) {

		while (list) {
			if (!ay_conversation_buddy_connected(ecr, list->name)) {
				ay_conversation_fellows_append(ecr, list->name,
					list->name);

				ecr->num_fellows++;


				if ((ea = find_account_with_ela(list->name,
							ela))) {
					eb_debug(DBG_IRC,
						"Logged in NAMEREPLY user: %s\n",
						buddy_name);

					eia = (ay_irc_account *)ea->
						protocol_account_data;


					if (eia->status == IRC_OFFLINE)
						buddy_login(ea);

					buddy_update_status(ea);
					eia->status = IRC_ONLINE;
				}
			}
			list = list->next;
		}
	}
}
