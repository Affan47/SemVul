up_backend_has_encrypted_swap (UpBackend *backend)
{
	gchar *contents_swaps = NULL;
	gchar *contents_crypttab = NULL;
	gchar **lines_swaps = NULL;
	gchar **lines_crypttab = NULL;
	GError *error = NULL;
	gboolean ret;
	gboolean encrypted_swap = FALSE;
	const gchar *filename_swaps = "/proc/swaps";
	const gchar *filename_crypttab = "/etc/crypttab";
	GPtrArray *devices = NULL;
	gchar *device;
	guint i, j;


	ret = g_file_get_contents (filename_swaps, &contents_swaps, NULL, &error);
	if (!ret) {
		g_warning ("failed to open %s: %s", filename_swaps, error->message);
		g_error_free (error);
		goto out;
	}


	ret = g_file_get_contents (filename_crypttab, &contents_crypttab, NULL, &error);
	if (!ret) {
		if (error->code != G_FILE_ERROR_NOENT) {
			g_warning ("failed to open %s: %s", filename_crypttab, error->message);
		}
		g_error_free (error);
		goto out;
	}


	lines_swaps = g_strsplit (contents_swaps, "\n", -1);
	lines_crypttab = g_strsplit (contents_crypttab, "\n", -1);


	devices = g_ptr_array_new_with_free_func (g_free);
	for (i=0; lines_swaps[i] != NULL; i++) {


		if (lines_swaps[i][0] != '/')
			continue;


		g_strdelimit (lines_swaps[i], "\t ", '\0');


		device = g_path_get_basename (lines_swaps[i]);
		g_debug ("adding swap device: %s", device);
		g_ptr_array_add (devices, device);
	}


	if (devices->len == 0) {
		g_debug ("no swap devices");
		goto out;
	}


	for (i=0; lines_crypttab[i] != NULL; i++) {


		if (lines_crypttab[i][0] == '#' ||
		    lines_crypttab[i][0] == '\n' ||
		    lines_crypttab[i][0] == '\t' ||
		    lines_crypttab[i][0] == '\0')
			continue;


		g_strdelimit (lines_crypttab[i], "\t ", '\0');


		for (j=0; j<devices->len; j++) {
			device = g_ptr_array_index (devices, j);
			if (g_strcmp0 (device, lines_crypttab[i]) == 0) {
				g_debug ("swap device %s is encrypted (so cannot hibernate)", device);
				encrypted_swap = TRUE;
				goto out;
			}
			g_debug ("swap device %s is not encrypted (allows hibernate)", device);
		}
	}

out:
	if (devices != NULL)
		g_ptr_array_unref (devices);
	g_free (contents_swaps);
	g_free (contents_crypttab);
	g_strfreev (lines_swaps);
	g_strfreev (lines_crypttab);
	return encrypted_swap;
}
