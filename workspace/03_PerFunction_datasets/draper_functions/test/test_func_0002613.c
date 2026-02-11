on_themed_file_new(G_GNUC_UNUSED GtkWidget* widget, gcp::Window* Win)
{
	new gcp::NewFileDlg (Win->GetApplication ());
}
