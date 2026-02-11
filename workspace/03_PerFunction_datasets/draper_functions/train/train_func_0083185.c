atcommand_blacksmith(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	nullpo_retr(-1, sd);

	ranking_display(sd,RK_BLACKSMITH,0,MAX_RANKER-1);

	return 0;
}
