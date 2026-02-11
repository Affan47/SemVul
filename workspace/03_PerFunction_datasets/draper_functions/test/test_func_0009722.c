plugin_save_list(void)
{
	gchar *rcpath, *block;
	PrefFile *pfile;
	GSList *type_cur, *plugin_cur;
	Plugin *plugin;

	for (type_cur = plugin_types; type_cur != NULL; type_cur = g_slist_next(type_cur)) {
		rcpath = g_strconcat(get_rc_dir(), G_DIR_SEPARATOR_S, COMMON_RC, NULL);
#ifdef G_OS_WIN32
		block = g_strconcat("PluginsWin32_", type_cur->data, NULL);
#else
		block = g_strconcat("Plugins_", type_cur->data, NULL);
#endif
		if ((pfile = prefs_write_open(rcpath)) == NULL ||
		    (prefs_set_block_label(pfile, block) < 0)) {
			g_warning("failed to write plugin list\n");
			g_free(rcpath);
			return;
		}
		g_free(block);

		for (plugin_cur = plugins; plugin_cur != NULL; plugin_cur = g_slist_next(plugin_cur)) {
			plugin = (Plugin *) plugin_cur->data;

			if (plugin->unloaded_hidden)
				continue;

			if (!strcmp(plugin->type(), type_cur->data)) {
				gchar * name = plugin_canonical_name(plugin);
				int err = fprintf(pfile->fp, "%s\n", name);
				g_free(name);
				if (err < 0)
					goto revert;
			}
		}
		for (plugin_cur = unloaded_plugins; plugin_cur != NULL; plugin_cur = g_slist_next(plugin_cur)) {
			plugin = (Plugin *) plugin_cur->data;

			if (plugin->unloaded_hidden)
				continue;

			if (!strcmp(plugin->type(), type_cur->data)) {
				gchar * name = plugin_canonical_name(plugin);
				int err = fprintf(pfile->fp, "%s\n", name);
				g_free(name);
				if (err < 0)
					goto revert;
			}
		}
		if (fprintf(pfile->fp, "\n") < 0)
			goto revert;

		if (prefs_file_close(pfile) < 0)
			g_warning("failed to write plugin list\n");

		g_free(rcpath);

		continue;

revert:
		g_warning("failed to write plugin list\n");
		if (prefs_file_close_revert(pfile) < 0)
			g_warning("failed to revert plugin list\n");

		g_free(rcpath);
	}
}
