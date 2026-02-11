e_cal_backend_cache_put_timezone (ECalBackendCache *cache,
                                  const icaltimezone *zone)
{
	ECalBackendCachePrivate *priv;
	icaltimezone *new_zone;
	icalcomponent *icalcomp;
	gboolean retval;
	gchar *obj;

	g_return_val_if_fail (E_IS_CAL_BACKEND_CACHE (cache), FALSE);
	g_return_val_if_fail (zone != NULL, FALSE);

	priv = cache->priv;


	icalcomp = icaltimezone_get_component ((icaltimezone *) zone);
	if (!icalcomp)
		return FALSE;

	obj = icalcomponent_as_ical_string_r (icalcomp);
	if (e_file_cache_get_object (E_FILE_CACHE (cache), icaltimezone_get_tzid ((icaltimezone *) zone))) {
		retval = e_file_cache_replace_object (
			E_FILE_CACHE (cache),
			icaltimezone_get_tzid ((icaltimezone *) zone),
			obj);
	} else {
		retval = e_file_cache_add_object (
			E_FILE_CACHE (cache),
			icaltimezone_get_tzid ((icaltimezone *) zone),
			obj);
	}
	g_free (obj);

	if (!retval)
		return FALSE;


	new_zone = icaltimezone_new ();
	icaltimezone_set_component (new_zone, icalcomponent_new_clone (icalcomp));
	g_hash_table_insert (priv->timezones, g_strdup (icaltimezone_get_tzid (new_zone)), new_zone);

	return TRUE;
}
