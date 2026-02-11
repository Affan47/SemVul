url (GSList const	*args,
     void		*user_data)
{
	char *cwd;
	char *path;
	char *uri;

	g_return_val_if_fail (args && args->data, NULL);

	cwd = g_get_current_dir ();
	path = g_build_filename (cwd, args->data, NULL);
	g_free (cwd), cwd = NULL;
	uri = g_strdup_printf ("file://%s", path);
	g_free (path), path = NULL;

	return uri;
}
