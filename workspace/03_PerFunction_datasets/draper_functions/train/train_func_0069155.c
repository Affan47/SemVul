e2_dialog_run (GtkWidget *dialog, GtkWidget *parent, E2_DialogFlags flags)
{

	if (flags & E2_DIALOG_THREADED)
		gdk_threads_enter ();
	if ((flags & E2_DIALOG_RUNMODAL) && (parent != NULL))
		gtk_widget_set_sensitive (parent, FALSE);
	if (flags & E2_DIALOG_DONT_SHOW_ALL)
		gtk_widget_show (dialog);
	else
		gtk_widget_show_all (dialog);
	if (flags & E2_DIALOG_THREADED)
		gdk_threads_leave ();

	if (flags & E2_DIALOG_RUNMODAL)
	{
		if (flags & E2_DIALOG_THREADED)
			gdk_threads_enter ();
		gint ret = gtk_dialog_run (GTK_DIALOG (dialog));
		if (parent != NULL)
			gtk_widget_set_sensitive (parent, TRUE);

		if (flags & E2_DIALOG_FREE)
			gtk_widget_destroy (dialog);
		gtk_widget_grab_focus (curr_view->treeview);
		if (flags & E2_DIALOG_THREADED)
			gdk_threads_leave ();
		return ret;
	}
	return 0;
}
