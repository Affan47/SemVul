row_callback(GtkWidget *wid, gpointer user)
{
	if(GTK_IS_HBOX(wid))
		gtk_container_foreach(GTK_CONTAINER(wid), btn_callback, user);
	else
		fprintf(stderr, "**BUTTONS: Unexpected non-hbox widget found!\n");
}
