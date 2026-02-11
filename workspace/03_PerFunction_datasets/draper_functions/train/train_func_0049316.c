pidff_find_special_fields(struct pidff_device *pidff)
{
	hid_dbg(pidff->hid, "finding special fields\n");

	pidff->create_new_effect_type =
		pidff_find_special_field(pidff->reports[PID_CREATE_NEW_EFFECT],
					 0x25, 1);
	pidff->set_effect_type =
		pidff_find_special_field(pidff->reports[PID_SET_EFFECT],
					 0x25, 1);
	pidff->effect_direction =
		pidff_find_special_field(pidff->reports[PID_SET_EFFECT],
					 0x57, 0);
	pidff->device_control =
		pidff_find_special_field(pidff->reports[PID_DEVICE_CONTROL],
					 0x96, 1);
	pidff->block_load_status =
		pidff_find_special_field(pidff->reports[PID_BLOCK_LOAD],
					 0x8b, 1);
	pidff->effect_operation_status =
		pidff_find_special_field(pidff->reports[PID_EFFECT_OPERATION],
					 0x78, 1);

	hid_dbg(pidff->hid, "search done\n");

	if (!pidff->create_new_effect_type || !pidff->set_effect_type) {
		hid_err(pidff->hid, "effect lists not found\n");
		return -1;
	}

	if (!pidff->effect_direction) {
		hid_err(pidff->hid, "direction field not found\n");
		return -1;
	}

	if (!pidff->device_control) {
		hid_err(pidff->hid, "device control field not found\n");
		return -1;
	}

	if (!pidff->block_load_status) {
		hid_err(pidff->hid, "block load status field not found\n");
		return -1;
	}

	if (!pidff->effect_operation_status) {
		hid_err(pidff->hid, "effect operation field not found\n");
		return -1;
	}

	pidff_find_special_keys(pidff->control_id, pidff->device_control,
				pidff_device_control,
				sizeof(pidff_device_control));

	PIDFF_FIND_SPECIAL_KEYS(control_id, device_control, device_control);

	if (!PIDFF_FIND_SPECIAL_KEYS(type_id, create_new_effect_type,
				     effect_types)) {
		hid_err(pidff->hid, "no effect types found\n");
		return -1;
	}

	if (PIDFF_FIND_SPECIAL_KEYS(status_id, block_load_status,
				    block_load_status) !=
			sizeof(pidff_block_load_status)) {
		hid_err(pidff->hid,
			"block load status identifiers not found\n");
		return -1;
	}

	if (PIDFF_FIND_SPECIAL_KEYS(operation_id, effect_operation_status,
				    effect_operation_status) !=
			sizeof(pidff_effect_operation_status)) {
		hid_err(pidff->hid, "effect operation identifiers not found\n");
		return -1;
	}

	return 0;
}
