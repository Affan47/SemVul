hdhomerun_device_get_tuner_status_lock_is_bcast(struct hdhomerun_tuner_status_t *status)
{
	if (strcmp(status->lock_str, "8vsb") == 0) {
		return TRUE;
	}
	if (strncmp(status->lock_str, "t8", 2) == 0) {
		return TRUE;
	}
	if (strncmp(status->lock_str, "t7", 2) == 0) {
		return TRUE;
	}
	if (strncmp(status->lock_str, "t6", 2) == 0) {
		return TRUE;
	}

	return FALSE;
}
