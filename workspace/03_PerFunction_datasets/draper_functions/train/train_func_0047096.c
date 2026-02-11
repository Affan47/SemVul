fm_get_user_input(GtkWindow* parent, const char* title, const char* msg, const char* default_text)
{
    GtkDialog* dlg = _fm_get_user_input_dialog( parent, title, msg);
    GtkEntry* entry = GTK_ENTRY(gtk_entry_new());
    gtk_entry_set_activates_default(entry, TRUE);

    if(default_text && default_text[0])
        gtk_entry_set_text(entry, default_text);

    return _fm_user_input_dialog_run(dlg, entry, NULL);
}
