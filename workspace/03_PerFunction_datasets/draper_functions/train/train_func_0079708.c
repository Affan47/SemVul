pk_client_convert_real_paths (gchar **paths, GError **error)
{
	guint i;
	guint len;
	gchar **res;


	len = g_strv_length (paths);
	res = g_new0 (gchar *, len+1);


	for (i=0; i<len; i++) {
		res[i] = pk_client_real_path (paths[i]);
		if (res[i] == NULL) {

			g_set_error (error, PK_CLIENT_ERROR, PK_CLIENT_ERROR_INVALID_INPUT, "could not resolve: %s", paths[i]);
			g_strfreev (res);
			res = NULL;
			goto out;
		}
	}
out:
	return res;
}
