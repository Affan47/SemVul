get_time_from_time_string (const char *time_string,
			   time_t *time)
{
	long scanned_time;
	char c;

	g_assert (time != NULL);


	if (time_string == NULL ||
	    sscanf (time_string, "%ld%c", &scanned_time, &c) != 1) {
		return FALSE;
	}
	*time = (time_t) scanned_time;
	return TRUE;
}
