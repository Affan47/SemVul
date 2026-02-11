reset(char *type, gn_data *data, struct gn_statemachine *state)
{
	gn_data_clear(data);
	data->reset_type = 0x03;

	if (type) {
		if (!strcmp(type, "soft"))
			data->reset_type = 0x03;
		else
			if (!strcmp(type, "hard")) {
				data->reset_type = 0x04;
			} else {
				fprintf(stderr, _("What kind of reset do you want??\n"));
				return -1;
			}
	}

	return gn_sm_functions(GN_OP_Reset, data, state);
}
