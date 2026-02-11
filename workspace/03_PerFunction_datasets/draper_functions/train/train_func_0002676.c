map_addobject(struct block_list *bl)
{
	static int last_object_id = MIN_FLOORITEM - 1;
	int i;

	nullpo_retr(0, bl);

	for(i = last_object_id + 1; i != last_object_id; i++) {
		if(i == MAX_FLOORITEM)
			i = MIN_FLOORITEM;

		if(object[i] == NULL)
			break;
	}
	if(i == last_object_id) {
		if(battle_config.error_log)
			printf("no free object id\n");
		return 0;
	}
	last_object_id = i;
	object[i] = bl;

	return i;
}
