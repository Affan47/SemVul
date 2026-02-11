atcommand_item(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	char item_name[100];
	int number = 0, item_id = 0;
	struct item_data *item_data;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	if (sscanf(message, "%99s %d", item_name, &number) < 1)
		return -1;

	if (number <= 0)
		number = 1;

	item_id = atoi(item_name);
	if (item_id < 0)
		item_id = itemdb_searchrandomid(-item_id);

	if (item_id > 0) {
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
		int loop = 1, get_count = number;
		struct item item_tmp;

		if (itemdb_isarmor(item_data->nameid) || itemdb_isweapon(item_data->nameid) ||
		    item_data->flag.pet_egg || item_data->flag.pet_acce) {
			loop = number;
			get_count = 1;
		}
		for (i = 0; i < loop; i++) {
			memset(&item_tmp, 0, sizeof(item_tmp));
			item_tmp.nameid = item_id;
			item_tmp.identify = 1;
			if ((flag = pc_additem(sd, &item_tmp, get_count)))
				clif_additem(sd, 0, 0, flag);
		}
		clif_displaymessage(fd, msg_txt(18));
	} else {
		clif_displaymessage(fd, msg_txt(19));
	}

	return 0;
}
