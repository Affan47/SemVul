atcommand_viewclass(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	int view_class;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%d", &view_class) < 1)
		return -1;

	sd->view_class = view_class;
	clif_changelook(&sd->bl,LOOK_BASE,view_class);

	return 0;
}
