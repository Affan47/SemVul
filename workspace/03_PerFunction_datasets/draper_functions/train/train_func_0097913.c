get_username_handler(CMD_DATA *p_cmd, int current_nr, void *p_context)
{
	DYN_DNS_CLIENT *p_self = (DYN_DNS_CLIENT *) p_context;

	if (p_self == NULL)
		return RC_INVALID_POINTER;

	if (sizeof(p_self->info[curr_info].credentials.my_username) < strlen(p_cmd->argv[current_nr]))
		return  RC_DYNDNS_BUFFER_TOO_SMALL;

	strcpy(p_self->info[curr_info].credentials.my_username, p_cmd->argv[current_nr]);

	return RC_OK;
}
