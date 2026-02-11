phone_info_incoming(int messagetype, unsigned char *message, int length, gn_data *data, struct gn_statemachine *state)
{
	unsigned char *pos;

	if (data->model) {
		snprintf(data->model, 6, "%s", message + 21);
	}
	if (data->revision) {
		snprintf(data->revision, GN_REVISION_MAX_LENGTH, "SW: %s", message + 6);
		if ((pos = strchr(data->revision, '\n')) != NULL) *pos = 0;
	}
	dprintf("Phone info:\n%s\n", message + 4);
	return GN_ERR_NONE;
}
