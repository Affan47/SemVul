gsf_output_gzip_new (GsfOutput *sink, GError **err)
{
	GsfOutput *output;
	GError const *con_err;

	g_return_val_if_fail (GSF_IS_OUTPUT (sink), NULL);

	output = g_object_new (GSF_OUTPUT_GZIP_TYPE, "sink", sink, NULL);

	con_err = gsf_output_error (output);

	if (con_err) {
		if (err)
			*err = g_error_copy (con_err);
		g_object_unref (output);
		return NULL;
	}

	return output;
}
