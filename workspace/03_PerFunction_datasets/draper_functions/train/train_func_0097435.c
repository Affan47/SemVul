atcommand_item3(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	struct map_session_data *pl_sd;
	struct item_data *item_data;
	char item_name[100];
	char character[100];
	int item_id = 0, number = 0;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	if (sscanf(message, "%99s %d %99[^\n]", item_name, &number, character) < 3)
		return -1;

	if (number <= 0)
		number = 1;
	if ((pl_sd = map_nick2sd(character)) == NULL) {
		clif_displaymessage(fd, msg_txt(3));
		return 0;
	}

	if ((item_id = atoi(item_name)) > 0) {
		if (battle_config.item_check) {
			item_data = itemdb_exists(item_id);
			if (item_data == NULL || !itemdb_available(item_id))
				item_id = 0;
		} else {
			item_data = itemdb_search(item_id);
		}
	} else {
		item_data = itemdb_searchname(item_name);
		if (item_data && (!battle_config.item_check || itemdb_available(item_data->nameid)))
			item_id = item_data->nameid;
	}

	if (item_id > 0) {
		int i, flag;
		int loop = 1, get_count = number, equip_item = 0;
		struct item item_tmp;

		if (itemdb_isarmor(item_data->nameid) || itemdb_isweapon(item_data->nameid) ||
		    item_data->flag.pet_egg || item_data->flag.pet_acce) {
			loop = number;
			get_count = 1;
			equip_item = 1;
		}
		for (i = 0; i < loop; i++) {
			memset(&item_tmp, 0, sizeof(item_tmp));
			item_tmp.nameid    = item_id;
			item_tmp.identify  = 1;
			item_tmp.refine    = 0;
			item_tmp.attribute = 0;
			item_tmp.card[0]   = (equip_item) ? 0x00ff : 0x00fe;
			item_tmp.card[1]   = 0;
			*((int *)(&item_tmp.card[2])) = pl_sd->status.char_id;
			if ((flag = pc_additem(sd, &item_tmp, get_count)))
				clif_additem(sd, 0, 0, flag);
		}
		clif_displaymessage(fd, msg_txt(18));
	} else {
		clif_displaymessage(fd, msg_txt(19));
	}

	return 0;
}
