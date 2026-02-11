atcommand_onlymes(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	char temp[200], buf[512];

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%199[^#\n]", temp) < 1)
		return -1;

	snprintf(buf, sizeof(buf), "%s %s : %s", msg_txt(156), sd->status.name, temp);
	clif_onlymessage(buf, strlen(buf) + 1);

	return 0;
}
