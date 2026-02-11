rename_main_window(char const* filename, GtkWidget *main_win)
{
	GString *win_title=g_string_new(NULL);
	static GtkWidget *win=NULL;

	if( main_win != NULL )
	win = main_win;

	g_assert(win != NULL);

	g_string_printf (win_title,"%s version %s: %s", WIN_TITLE, VERSION, filename);
	gtk_window_set_title(GTK_WINDOW(win), win_title->str);
	g_string_free(win_title,TRUE);
}
