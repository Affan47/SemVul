homun_hungry_cry(int tid,unsigned int tick,int id,void *data)
{
	struct map_session_data *sd = map_id2sd(id);

	if(sd == NULL || sd->hd == NULL)
		return 1;

	if(sd->hd->hungry_cry_timer != tid) {
		if(battle_config.error_log)
			printf("homun_hungry_cry_timer %d != %d\n",sd->hd->hungry_cry_timer,tid);
		return 0;
	}
	sd->hd->hungry_cry_timer = -1;
	clif_emotion(&sd->hd->bl,28);
	sd->hd->hungry_cry_timer = add_timer(tick+20*1000,homun_hungry_cry,sd->bl.id,NULL);

	return 0;
}
