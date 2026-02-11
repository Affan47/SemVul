atcommand_statuspoint(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	int point;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	point = atoi(message);
	if (point > 0 || sd->status.status_point + point >= 0) {
		sd->status.status_point += point;
		clif_updatestatus(sd, SP_STATUSPOINT);
	} else {
		clif_displaymessage(fd, msg_txt(41));
	}

	return 0;
}
