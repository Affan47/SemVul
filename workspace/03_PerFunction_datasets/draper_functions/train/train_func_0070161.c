control_config_do_reset()
{
	int i, j, total = 0;
	config_item_undo *ptr;
	config_item item;


	for (i=0; i<CCFG_MAX; i++) {
		if ((Control_config[i].key_id != Control_config[i].key_default) || (Control_config[i].joy_id != Control_config[i].joy_default)) {
			total++;
		}
	}

	for (i=0; i<NUM_JOY_AXIS_ACTIONS; i++) {
		if ((Axis_map_to[i] != control_config_axis_default(i)) || (Invert_axis[i] != Invert_axis_defaults[i])) {
			total++;
		}
	}

	if (!total) {
		gamesnd_play_iface(SND_GENERAL_FAIL);
		return -1;
	}


	ptr = get_undo_block(total);
	for (i=j=0; i<CCFG_MAX; i++) {
		if ((Control_config[i].key_id != Control_config[i].key_default) || (Control_config[i].joy_id != Control_config[i].joy_default)) {
			ptr->index[j] = i;
			ptr->list[j] = Control_config[i];
			j++;
		}
	}

	for (i=0; i<NUM_JOY_AXIS_ACTIONS; i++) {
		if ((Axis_map_to[i] != control_config_axis_default(i)) || (Invert_axis[i] != Invert_axis_defaults[i])) {
			memset( &item, 0, sizeof(config_item) );

			item.joy_id = (short) Axis_map_to[i];
			item.used = Invert_axis[i];

			ptr->index[j] = i | JOY_AXIS;
			ptr->list[j] = item;
			j++;
		}
	}
	Assert(j == total);
	control_config_reset_defaults();
	control_config_conflict_check();
	control_config_list_prepare();
	gamesnd_play_iface(SND_RESET_PRESSED);
	return 0;
}
