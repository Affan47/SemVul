value2human(unsigned long bytes, double time, double *data, double *speed,
	    char *metric)
{
	if (bytes > 1000 && bytes < 1000 * 1000) {
		*data = ((double) bytes) / 1000;
		*speed = *data / time;
		strcpy(metric, "KB");
		return;
	} else if (bytes >= 1000 * 1000 && bytes < 1000 * 1000 * 1000) {
		*data = ((double) bytes) / (1000 * 1000);
		*speed = *data / time;
		strcpy(metric, "MB");
		return;
	} else if (bytes >= 1000 * 1000 * 1000) {
		*data = ((double) bytes) / (1000 * 1000 * 1000);
		*speed = *data / time;
		strcpy(metric, "GB");
		return;
	} else {
		*data = (double) bytes;
		*speed = *data / time;
		strcpy(metric, "bytes");
		return;
	}
}
