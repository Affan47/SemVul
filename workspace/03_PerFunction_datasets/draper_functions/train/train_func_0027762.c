atcommand_summon(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	char mob_name[100];
	int mob_id = 0;
	int x, y, id;
	struct mob_data *md;
	unsigned int tick = gettick();

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%99s", mob_name) < 1)
		return -1;

	if ((mob_id = atoi(mob_name)) == 0)
		mob_id = mobdb_searchname(mob_name);
	if (mob_id == 0)
		return -1;

	x = sd->bl.x + (atn_rand() % 10 - 5);
	y = sd->bl.y + (atn_rand() % 10 - 5);

	id = mob_once_spawn(sd, sd->bl.m, x, y, sd->status.name, mob_id, 1, "");
	if ((md = map_id2md(id)) != NULL) {
		md->state.special_mob_ai = 1;
		md->master_id   = sd->bl.id;
		md->mode        = mob_db[md->class_].mode | MD_AGGRESSIVE;
		md->deletetimer = add_timer(tick+60000,mob_timer_delete,id,NULL);
		clif_misceffect2(&md->bl,344);
	}
	clif_skill_poseffect(&sd->bl,AM_CALLHOMUN,1,x,y,tick);

	return 0;
}
