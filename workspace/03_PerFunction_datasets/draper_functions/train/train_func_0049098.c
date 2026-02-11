NK6510_GetFileById(gn_data *data, struct gn_statemachine *state)
{
	unsigned char req[] = {FBUS_FRAME_HEADER, 0x0e, 0x00, 0x00,
				0x00, 0x01,
				0x00, 0x00,
				0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00};
	gn_error err = GN_ERR_NONE;
	int i, length;


	if (data->progress_indication) {
		DRVINSTANCE(state)->progress_indication = data->progress_indication;
		DRVINSTANCE(state)->progress_callback_data = data->callback_data;
	}

	if (!data->file)
		return GN_ERR_INTERNALERROR;

	length = data->file->id[0];
	for (i = 0; i < length; i++) {
		req[8 + i] = data->file->id[i+1];
	}
	length /= 2;
	req[6] = (length & 0xff00) >> 8;
	req[7] = (length & 0x00ff);

	while (data->file->togo > 0) {
		int progress, offset;

		offset = 9 + 2 * length;
		i = data->file->file_length - data->file->togo;
		req[offset] = (i & 0xff0000) >> 16;
		req[offset + 1] = (i & 0xff00) >> 8;
		req[offset + 2] = i & 0xff;
		if (data->file->togo > 0x100) {
			req[offset + 5] = 0x01;
		} else {
			req[offset + 4] = (data->file->togo & 0xff0000) >> 16;
			req[offset + 5] = (data->file->togo & 0xff00) >> 8;
			req[offset + 6] = data->file->togo & 0xff;
		}
		if (sm_message_send(sizeof(req), NK6510_MSG_FILE, req, state))
			return GN_ERR_NOTREADY;
		err = sm_block(NK6510_MSG_FILE, data, state);
		if (err != GN_ERR_NONE)
			return err;
		progress = 100 * (data->file->file_length - data->file->togo) / data->file->file_length;
		if (!DRVINSTANCE(state)->progress_indication) {
			fprintf(stderr, _("Progress: %3d%% completed"), progress);

			fprintf(stderr, "\r");
		} else
			DRVINSTANCE(state)->progress_indication(progress, DRVINSTANCE(state)->progress_callback_data);
	}
	if (!DRVINSTANCE(state)->progress_indication)
		fprintf(stderr, "\n");

	return err;
}
