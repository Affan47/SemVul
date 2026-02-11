fpm_question(GtkWindow *win, gchar *message)
{
    GtkWidget *dw;
    dw = gtk_message_dialog_new (GTK_WINDOW(win),
			GTK_DIALOG_DESTROY_WITH_PARENT,
			GTK_MESSAGE_QUESTION,
			GTK_BUTTONS_YES_NO,
			"%s",
			message);
    gtk_window_set_title (GTK_WINDOW(dw), _("Question"));

    gint result = gtk_dialog_run (GTK_DIALOG (dw));
    if(result != GTK_RESPONSE_NONE) gtk_widget_destroy (dw);

    return(result);
}
