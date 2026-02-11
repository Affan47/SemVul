gsf_output_gio_new_for_uri (char const *uri, GError **err)
{
	GFile *file;
	GsfOutput *output;

	g_return_val_if_fail (uri != NULL, NULL);

	file = g_file_new_for_uri (uri);
	output = gsf_output_gio_new_full (file, err);
	g_object_unref (file);

	return output;
}
