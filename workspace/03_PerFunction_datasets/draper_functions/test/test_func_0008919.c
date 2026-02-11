guild_send_xy_clear(struct guild *g)
{
	int i;

	nullpo_retv(g);

	for(i=0; i < g->max_member; i++) {
		struct map_session_data *sd;
		if((sd = g->member[i].sd) != NULL) {
			sd->guild_x = -1;
			sd->guild_y = -1;
		}
	}

	return;
}
