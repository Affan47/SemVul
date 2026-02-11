cd_client_import_mkdir_and_copy (GFile *source,
				 GFile *destination,
				 GCancellable *cancellable,
				 GError **error)
{
	gboolean ret;
	GFile *parent;

	g_return_val_if_fail (source != NULL, FALSE);
	g_return_val_if_fail (destination != NULL, FALSE);


	parent = g_file_get_parent (destination);


	if (!g_file_query_exists (parent, cancellable)) {
		ret = g_file_make_directory_with_parents (parent, cancellable, error);
		if (!ret)
			goto out;
	}


	ret = g_file_copy (source, destination,
			   G_FILE_COPY_OVERWRITE,
			   cancellable, NULL, NULL, error);
	if (!ret)
		goto out;
out:
	g_object_unref (parent);
	return ret;
}
