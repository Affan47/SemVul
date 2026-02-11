selwatch_get_lastid(struct ipmi_intf * intf)
{
	int next_id = 0;
	uint16_t curr_id = 0;
	struct sel_event_record evt;

	if (selwatch_count == 0)
		return 0;

	while (next_id != 0xffff) {
		curr_id = next_id;
		lprintf(LOG_DEBUG, "SEL Next ID: %04x", curr_id);

		next_id = ipmi_sel_get_std_entry(intf, curr_id, &evt);
		if (next_id < 0)
			break;
		if (next_id == 0) {


			next_id = ipmi_sel_get_std_entry(intf, curr_id, &evt);
			if (next_id <= 0)
				break;
		}
	}

	lprintf(LOG_DEBUG, "SEL lastid is %04x", curr_id);

	return curr_id;
}
