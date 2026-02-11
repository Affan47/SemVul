callback_send_ping(void *user, const char *address, const char *message)
{
	if(strncmp(message, "DESCRIBE", 8) == 0 && message[8] == ' ')
		vs_master_handle_describe(address, message + 9);
}
