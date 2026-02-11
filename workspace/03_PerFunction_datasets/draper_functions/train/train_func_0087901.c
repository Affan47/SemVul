gamt_getstring(GtkWidget *window, char *title, char *message,
			  char *dest, int dlen, int hide)
{
    GtkWidget *dialog, *label, *entry;
    const char *txt;
    int retval;


    dialog = gtk_dialog_new_with_buttons(title,
					 GTK_WINDOW(window),
                                         GTK_DIALOG_DESTROY_WITH_PARENT,
					 GTK_STOCK_OK,
					 GTK_RESPONSE_ACCEPT,
					 GTK_STOCK_CANCEL,
					 GTK_RESPONSE_REJECT,
                                         NULL);
    gtk_dialog_set_default_response(GTK_DIALOG(dialog), GTK_RESPONSE_ACCEPT);

    label = gtk_label_new(message);
    gtk_misc_set_alignment(GTK_MISC(label), 0, 0.5);

    entry = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(entry), dest);
    gtk_entry_set_activates_default(GTK_ENTRY(entry), TRUE);
    if (hide)
	gtk_entry_set_visibility(GTK_ENTRY(entry), FALSE);

    gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox), label);
    gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox), entry);
    gtk_box_set_spacing(GTK_BOX(GTK_DIALOG(dialog)->vbox), 10);
#if 0
    gtk_container_set_border_width(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox), 10);
#endif


    gtk_widget_show_all(dialog);
    switch (gtk_dialog_run(GTK_DIALOG(dialog))) {
    case GTK_RESPONSE_ACCEPT:
	txt = gtk_entry_get_text(GTK_ENTRY(entry));
	snprintf(dest, dlen, "%s", txt);
	retval = 0;
	break;
    default:
	retval = -1;
	break;
    }
    gtk_widget_destroy(dialog);
    return retval;
}
