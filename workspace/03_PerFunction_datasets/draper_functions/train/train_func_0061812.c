new_game()
{
	if (!okay_to_close())
		return;
	GtkFileSelection *fsel = Create_file_selection(
			"Choose new game directory",
			on_choose_new_game_dir, this);
	gtk_widget_show(GTK_WIDGET(fsel));
}
