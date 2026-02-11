atcommand_charstpoint(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	struct map_session_data *pl_sd;
	char character[100];
	int point = 0;

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%d %99[^\n]", &point, character) < 2)
		return -1;

	if ((pl_sd = map_nick2sd(character)) != NULL) {
		int new_status_point = (int)pl_sd->status.status_point + point;

		if (point > 0 && (point > 0x7FFF || new_status_point > 0x7FFF))
			new_status_point = 0x7FFF;
		else if (point < 0 && (point < -0x7FFF || new_status_point < 0))
			new_status_point = 0;
		if (new_status_point == (int)pl_sd->status.status_point)
			return -1;
		pl_sd->status.status_point = new_status_point;
		clif_updatestatus(pl_sd, SP_STATUSPOINT);
		msg_output(fd, msg_txt(102), character);
	} else {
		clif_displaymessage(fd, msg_txt(3));
	}

	return 0;
}
