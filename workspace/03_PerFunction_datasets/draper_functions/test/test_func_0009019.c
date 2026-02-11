e_cal_backend_cache_put_default_timezone (ECalBackendCache *cache,
                                          icaltimezone *default_zone)
{
	icalcomponent *icalcomp;
	gboolean retval;
	gchar *obj;

	g_return_val_if_fail (E_IS_CAL_BACKEND_CACHE (cache), FALSE);


	icalcomp = icaltimezone_get_component (default_zone);
	if (!icalcomp)
		return FALSE;

	obj = icalcomponent_as_ical_string_r (icalcomp);
	if (e_file_cache_get_object (E_FILE_CACHE (cache), "default_zone")) {
		retval = e_file_cache_replace_object (
			E_FILE_CACHE (cache), "default_zone",
			obj);
	} else {
		retval = e_file_cache_add_object (
			E_FILE_CACHE (cache),
			"default_zone",
			obj);
	}
	g_free (obj);

	if (!retval)
		return FALSE;

	return TRUE;

}
