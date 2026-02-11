ndmp_9to2_tape_open_request (
  ndmp9_tape_open_request *request9,
  ndmp2_tape_open_request *request2)
{
	int		n_error = 0;
	int		rc;

	rc = convert_enum_from_9 (ndmp_29_tape_open_mode, request9->mode);
	if (rc == NDMP_INVALID_GENERAL) {
		n_error++;
		request2->mode = request9->mode;
	} else {
		request2->mode = rc;
	}

	request2->device.name = NDMOS_API_STRDUP (request9->device);
	if (!request2->device.name) {
		return -1;
	}

	return n_error;
}
