ipmi_sdr_print_discrete_state_mini(const char *separator,
				   uint8_t sensor_type, uint8_t event_type,
				   uint8_t state1, uint8_t state2)
{
	uint8_t typ;
	struct ipmi_event_sensor_types *evt;
	int pre = 0, c = 0;

	if (state1 == 0 && (state2 & 0x7f) == 0)
		return;

	if (event_type == 0x6f) {
		evt = sensor_specific_types;
		typ = sensor_type;
	} else {
		evt = generic_event_types;
		typ = event_type;
	}

	for (; evt->type != NULL; evt++) {
		if (evt->code != typ)
			continue;

		if (evt->offset > 7) {
			if ((1 << (evt->offset - 8)) & (state2 & 0x7f)) {
				if (pre++ != 0)
					printf("%s", separator);
				printf("%s", evt->desc);
			}
		} else {
			if ((1 << evt->offset) & state1) {
				if (pre++ != 0)
					printf("%s", separator);
				printf("%s", evt->desc);
			}
		}
		c++;
	}
}
