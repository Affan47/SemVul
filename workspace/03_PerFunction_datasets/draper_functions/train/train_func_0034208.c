snprint_def_no_path_retry (char * buff, int len, void * data)
{
	if (conf->no_path_retry == DEFAULT_NO_PATH_RETRY)
		return 0;

	switch(conf->no_path_retry) {
	case NO_PATH_RETRY_UNDEF:
		break;
	case NO_PATH_RETRY_FAIL:
		return snprintf(buff, len, "fail");
	case NO_PATH_RETRY_QUEUE:
		return snprintf(buff, len, "queue");
	default:
		return snprintf(buff, len, "%i",
				conf->no_path_retry);
	}
	return 0;
}
