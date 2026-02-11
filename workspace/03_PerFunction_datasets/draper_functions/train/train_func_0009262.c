on_open_clicked                        (GtkToolButton   *toolbutton,
                                        gpointer         user_data)
{
	gchar *fn;

	if(user_data == NULL)
	{
		if(GFMFile.contents.group || GFMFile.contents.tigroup)
		{
			int result = msgbox_two(MSGBOX_YESNO, _("Do you want to save previous file?"));
			if(result == MSGBOX_YES)
				on_save_clicked(toolbutton,user_data);
		}

		fn = (char *)create_fsel(inst_paths.home_dir, "", "*.73?;*.82?;*.83?;*.8X?;*.85?;*.86?;*.89?;*.92?;*.9x?;*.V2?;*.tig", FALSE);
		if(fn == NULL)
			return;
	}
	else
	{

		fn = (char *)user_data;
	}

	if(tifiles_file_is_tigroup(fn))
		GFMFile.type = TIFILE_TIGROUP;
	else if(tifiles_file_is_regular(fn))
		GFMFile.type = TIFILE_GROUP;
	else
		return;

	file_load(fn);

	g_free(GFMFile.filename);
	GFMFile.filename = g_strdup(fn);

	enable_save(FALSE);
	enable_tree(TRUE);

	ctree_refresh();
	labels_refresh();

	g_free(inst_paths.home_dir);
	inst_paths.home_dir = g_path_get_dirname(GFMFile.filename);
}
