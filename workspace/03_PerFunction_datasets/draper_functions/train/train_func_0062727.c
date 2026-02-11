rb_canonicalise_uri (const char *uri)
{
	GFile *file;
	char *result = NULL;

	g_return_val_if_fail (uri != NULL, NULL);


	file = g_file_new_for_commandline_arg (uri);
	result = g_file_get_uri (file);
	g_object_unref (file);

	return result;
}
