read_gaussian_file(GabeditFileChooser *SelecFile, gint response_id)
{
	gchar *FileName;

	if(response_id != GTK_RESPONSE_OK) return;
 	FileName = gabedit_file_chooser_get_current_file(SelecFile);
	stopAnimation(NULL, NULL);

	freeGeometryConvergence();
  	rafreshList();
	read_gaussian_output(FileName);
}
