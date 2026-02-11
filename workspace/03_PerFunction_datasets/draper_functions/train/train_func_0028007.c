get_predefined_times(void)
{
	int h,m;
	GList *times = NULL;
	for (h = 0; h < 24; h++) {
		for (m = 0; m < 60; m += 15) {
			gchar *tmp = g_strdup_printf("%02d:%02d", h, m);
			times = g_list_append(times, tmp);
		}
	}
	return times;
}
