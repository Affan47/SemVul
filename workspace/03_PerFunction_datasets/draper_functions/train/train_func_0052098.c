doerror(int errnum)
{
	char	**evec = helpvec(errnum, 'E'), *newstr;
	GtkWidget  *msgw;
	if  (!evec[0])  {
		disp_arg[0] = errnum;
		free((char *) evec);
		evec = helpvec(10002, 'E');
	}
	newstr = makebigvec(evec);
	msgw = gtk_message_dialog_new(GTK_WINDOW(toplevel), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "%s", newstr);
	free(newstr);
	evec = helpvec(errnum, 'H');
	newstr = makebigvec(evec);
	gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(msgw), "%s", newstr);
	free(newstr);
	g_signal_connect_swapped(msgw, "response", G_CALLBACK(gtk_widget_destroy), msgw);
	gtk_widget_show(msgw);
	gtk_dialog_run(GTK_DIALOG(msgw));
}
