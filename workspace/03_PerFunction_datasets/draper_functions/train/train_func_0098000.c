on_group_clicked                       (GtkButton       *button,
                                        gpointer         user_data)
{
	int result;
	char **array;

	result = msgbox_three(_("TiGroup"), _("Single/Group"), _("File type?"));
	if(!result)
		return;

	array = create_fsels(inst_paths.home_dir, "", "*.73?;*.82?;*.83?;*.8X?;*.85?;*.86?;*.89?;*.92?;*.9x?;*.V2?");
	if(array == NULL)
		return;

	gfm_tifiles_group((const char **)array, result == MSGBOX_BUTTON1 ? TIFILE_TIGROUP : TIFILE_GROUP);
}
