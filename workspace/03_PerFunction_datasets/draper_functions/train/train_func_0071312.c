saveAsGabedit(GtkFileChooser *SelecFile, gint response_id)
{
	gchar *fileName;
	GtkWidget* contoursplot = g_object_get_data (G_OBJECT (SelecFile), "ContoursPLOT");

 	if(response_id != GTK_RESPONSE_OK) return;
	if(!GABEDIT_IS_ContoursPLOT(contoursplot)) return;
 	fileName = gtk_file_chooser_get_filename(SelecFile);
	gabedit_contoursplot_save_gabedit(contoursplot, fileName);
}
