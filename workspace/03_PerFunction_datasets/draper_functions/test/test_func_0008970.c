atcommand_questskill(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	int skill_id;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	skill_id = atoi(message);
	if (skill_get_inf2(skill_id) & INF2_QUEST) {
		pc_skill(sd, skill_id, 1, 0);
		clif_displaymessage(fd, msg_txt(70));
	}

	return 0;
}
