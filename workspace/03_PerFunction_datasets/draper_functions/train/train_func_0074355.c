atcommand_mobsearch(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	char mob_name[100], map_name[100] = "";
	const char *p;
	int mob_id, map_id = 0, number = 0;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%99s %99s", mob_name, map_name) < 1)
		return -1;

	if ((mob_id = atoi(mob_name)) == 0)
		mob_id = mobdb_searchname(mob_name);
	if (mob_id != -1 && mob_id != -2 && mob_id != -3 && !mobdb_checkid(mob_id)) {
		msg_output(fd, msg_txt(93), mob_name);
		return 0;
	}

	if (mob_id == -1)
		p = msg_txt(153);
	else if (mob_id == -2 || mob_id == -3)
		p = msg_txt(154);
	else if (mob_id > 0 && mob_id == atoi(mob_name) && mob_db[mob_id].jname[0])
		p = mob_db[mob_id].jname;
	else
		p = mob_name;

	if ((map_id = map_mapname2mapid(map_name)) < 0)
		map_id = sd->bl.m;

	msg_output(fd, msg_txt(92), p, map[map_id].name);

	map_foreachinarea(atcommand_mobsearch_sub, map_id, 0, 0, map[map_id].xs, map[map_id].ys, BL_MOB, mob_id, fd, &number);

	return 0;
}
