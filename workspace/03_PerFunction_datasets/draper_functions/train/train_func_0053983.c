NK6510_DeleteCalTodo_S40_30(gn_data *data, struct gn_statemachine *state, int type)
{
	unsigned char req[] = { FBUS_FRAME_HEADER,
				0x6f,
				0x00,
				0x00, 0x00, 0x00,
				0x00, 0x00};
	gn_calnote_list list;
	bool own_list = true;

	if (type != 0x00 && type != 0x01 && type != 0x02)
		return GN_ERR_INTERNALERROR;

	req[4] = type;

	if (data->calnote_list)
		own_list = false;
	else {
		memset(&list, 0, sizeof(gn_calnote_list));
		data->calnote_list = &list;
	}

	if (data->calnote_list->number == 0)
		NK6510_GetCalendarNotesInfo(data, state, type);

	if (data->calnote->location < data->calnote_list->number + 1 &&
	    data->calnote->location > 0) {
		req[8] = data->calnote_list->location[data->calnote->location - 1] >> 8;
		req[9] = data->calnote_list->location[data->calnote->location - 1] & 0xff;
	} else {
		return GN_ERR_INVALIDLOCATION;
	}

	if (own_list)
		data->calnote_list = NULL;
	map_del(&location_map, "calendar");
	SEND_MESSAGE_BLOCK(NK6510_MSG_CALENDAR, 10);
}
