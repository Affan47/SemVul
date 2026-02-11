eb_jabber_make_chat_room(char *name,
	eb_local_account *account, int is_public)
{
	Conversation *ecr;
	char *ptr = NULL;

	eb_debug(DBG_JBR, ">\n");
	j_list_agents();
	while (strstr(name, " "))
		*(strstr(name, " ")) = '_';

	ptr = name;

	while (*ptr) {
		*ptr = tolower(*ptr);
		ptr++;
	}

	ecr = ay_conversation_new(account, NULL, name, 1, is_public);

	eb_debug(DBG_JBR, "<\n");
	return ecr;
}
