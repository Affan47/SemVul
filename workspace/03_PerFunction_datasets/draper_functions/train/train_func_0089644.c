atcommand_ranking(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	int i;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%d", &i) < 1)
		return -1;
	if (i < 0 || i >= MAX_RANKER)
		return -1;

	ranking_display(sd,i,0,MAX_RANKER-1);

	return 0;
}
