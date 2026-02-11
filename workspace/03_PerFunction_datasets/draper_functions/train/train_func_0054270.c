application_compare_by_id (const GAppInfo *app_a,
			   const GAppInfo *app_b)
{
	const char *id_a, *id_b;

	id_a = g_app_info_get_id ((GAppInfo *)app_a);
	id_b = g_app_info_get_id ((GAppInfo *)app_b);

	if (id_a == NULL && id_b == NULL) {
		if (g_app_info_equal ((GAppInfo *)app_a, (GAppInfo *)app_b)) {
			return 0;
		}
		if ((gsize)app_a < (gsize) app_b) {
			return -1;
		}
		return 1;
	}

	if (id_a == NULL) {
		return -1;
	}

	if (id_b == NULL) {
		return 1;
	}


	return strcmp (id_a, id_b);
}
