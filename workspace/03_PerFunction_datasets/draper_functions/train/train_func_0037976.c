atcommand_character_save(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	char map_name[100];
	char character[100];
	struct map_session_data* pl_sd;
	int x, y;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%99s %d %d %99[^\n]", map_name, &x, &y, character) < 4)
		return -1;

	if ((pl_sd = map_nick2sd(character)) != NULL) {
		if (pc_isGM(sd) >= pc_isGM(pl_sd)) {
			int m;

			if (strstr(map_name, ".gat") == NULL && strlen(map_name) < 13) {
				strcat(map_name, ".gat");
			}
			m = map_mapname2mapid(map_name);
			if (x < 0 || y < 0 || (m >= 0 && (x >= map[m].xs || y >= map[m].ys))) {
				clif_displaymessage(fd, msg_txt(2));
			} else {
				pc_setsavepoint(pl_sd, map_name, x, y);
				clif_displaymessage(fd, msg_txt(57));
			}
		}
	} else {
		clif_displaymessage(fd, msg_txt(3));
	}

	return 0;
}
