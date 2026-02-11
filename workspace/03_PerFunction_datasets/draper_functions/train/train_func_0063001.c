pc_spiritball_timer(int tid,unsigned int tick,int id,void *data)
{
	struct map_session_data *sd = map_id2sd(id);
	int i;

	if(sd == NULL)
		return 1;

	if(sd->spiritball.timer[0] != tid) {
		if(battle_config.error_log)
			printf("spirit_timer %d != %d\n",sd->spiritball.timer[0],tid);
		return 0;
	}
	sd->spiritball.timer[0] = -1;
	for(i=1; i<sd->spiritball.num; i++) {
		sd->spiritball.timer[i-1] = sd->spiritball.timer[i];
		sd->spiritball.timer[i] = -1;
	}
	sd->spiritball.num--;
	if(sd->spiritball.num < 0)
		sd->spiritball.num = 0;
	clif_spiritball(sd);

	return 0;
}
