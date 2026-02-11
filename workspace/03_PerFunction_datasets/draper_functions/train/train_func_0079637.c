save_povray_file(GabeditFileChooser *w , gint response_id)
{
	gchar *fileName;
	gchar* message = NULL;
    	GtkWidget* m;

 	if(response_id != GTK_RESPONSE_OK) return;
	if(!GLArea) return;
 	fileName = gabedit_file_chooser_get_current_file(w);
	message = create_povray_file(fileName, FALSE, TRUE);
	if(message)
	{
    		m = Message(message,"Error",TRUE);
		gtk_window_set_modal (GTK_WINDOW (m), TRUE);
	}
}
