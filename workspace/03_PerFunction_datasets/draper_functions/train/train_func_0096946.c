cd_convert_ti3_ti3_to_ccmx (const gchar *reference_fn,
			    const gchar *measured_fn,
			    const gchar *device_fn,
			    GError **error)
{
	CdIt8 *it8_ccmx = NULL;
	CdIt8 *it8_measured = NULL;
	CdIt8 *it8_reference = NULL;
	gboolean ret;
	GFile *file_ccmx = NULL;
	GFile *file_measured = NULL;
	GFile *file_reference = NULL;


	it8_reference = cd_it8_new ();
	file_reference = g_file_new_for_path (reference_fn);
	ret = cd_it8_load_from_file (it8_reference,
				     file_reference,
				     error);
	if (!ret)
		goto out;


	it8_measured = cd_it8_new ();
	file_measured = g_file_new_for_path (measured_fn);
	ret = cd_it8_load_from_file (it8_measured,
				     file_measured,
				     error);
	if (!ret)
		goto out;


	it8_ccmx = cd_it8_new_with_kind (CD_IT8_KIND_CCMX);
	ret = cd_it8_utils_calculate_ccmx (it8_reference,
					   it8_measured,
					   it8_ccmx,
					   error);
	if (!ret)
		goto out;


	file_ccmx = g_file_new_for_path (device_fn);
	cd_it8_set_title (it8_ccmx, "Factory Calibration");
	cd_it8_set_originator (it8_ccmx, "cd-convert");
	cd_it8_add_option (it8_ccmx, "TYPE_FACTORY");
	ret = cd_it8_save_to_file (it8_ccmx, file_ccmx, error);
	if (!ret)
		goto out;
out:
	if (file_reference != NULL)
		g_object_unref (file_reference);
	if (file_measured != NULL)
		g_object_unref (file_measured);
	if (file_ccmx != NULL)
		g_object_unref (file_ccmx);
	if (it8_reference != NULL)
		g_object_unref (it8_reference);
	if (it8_measured != NULL)
		g_object_unref (it8_measured);
	if (it8_ccmx != NULL)
		g_object_unref (it8_ccmx);
	return ret;
}
