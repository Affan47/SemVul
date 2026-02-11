file_dialog_new(const gchar *title,
			    const gchar *role,
			    GtkWidget *parent,
			    void (*cancel_cb)(FileDialog *, gpointer), gpointer data)
{
	FileDialog *fdlg = NULL;

	fdlg = g_new0(FileDialog, 1);

	generic_dialog_setup(GENERIC_DIALOG(fdlg), title,
			     role, parent, FALSE,
			     (gpointer)cancel_cb, data);

	return fdlg;
}
