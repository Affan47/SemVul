wait_and_handle_event (long waittime, CameraEventType *type, int download) {
	int 		result;
	CameraEventType	evtype;
	void		*data;
	CameraFilePath	*path;

	if (!type) type = &evtype;
	evtype = GP_EVENT_UNKNOWN;
	data = NULL;
	result = gp_camera_wait_for_event(gp_params.camera, waittime, type, &data, gp_params.context);
	if (result == GP_ERROR_NOT_SUPPORTED) {
		*type = GP_EVENT_TIMEOUT;
		usleep(waittime*1000);
		return GP_OK;
	}
	if (result != GP_OK)
		return result;
	path = data;
	switch (*type) {
	case GP_EVENT_TIMEOUT:
		break;
	case GP_EVENT_CAPTURE_COMPLETE:
		break;
	case GP_EVENT_FOLDER_ADDED:
		if (!(gp_params.flags & FLAGS_QUIET))
			printf (_("Event FOLDER_ADDED %s/%s during wait, ignoring.\n"), path->folder, path->name);
		free (data);
		break;
	case GP_EVENT_FILE_ADDED:
		result = save_captured_file (path, download);
		free (data);

		break;
	case GP_EVENT_UNKNOWN:
#if 0
		printf (_("Event UNKNOWN %s during wait, ignoring.\n"), (char*)data);
#endif
		free (data);
		break;
	default:
		if (!(gp_params.flags & FLAGS_QUIET))
			printf (_("Unknown event type %d during bulb wait, ignoring.\n"), *type);
		break;
	}
	return result;
}
