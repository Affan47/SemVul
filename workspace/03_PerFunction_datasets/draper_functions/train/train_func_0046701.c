gsf_outfile_zip_constructor (GType                  type,
			     guint                  n_construct_properties,
			     GObjectConstructParam *construct_params)
{
	GsfOutfileZip *zip =(GsfOutfileZip *)
		(parent_class->constructor (type,
					    n_construct_properties,
					    construct_params));

	if (!zip->entry_name) {
		zip->vdir = gsf_zip_vdir_new ("", TRUE, NULL);
		zip->root_order = g_ptr_array_new ();
		zip->root = zip;


		gsf_output_set_name (GSF_OUTPUT (zip), gsf_output_name (zip->sink));
		gsf_output_set_container (GSF_OUTPUT (zip), NULL);
	}

	if (!gsf_output_get_modtime (GSF_OUTPUT (zip))) {
		GDateTime *modtime = g_date_time_new_now_utc ();
		gsf_output_set_modtime (GSF_OUTPUT (zip), modtime);
		g_date_time_unref (modtime);
	}

	return (GObject *)zip;
}
