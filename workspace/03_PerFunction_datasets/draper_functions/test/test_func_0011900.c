source_entry_notify_text_cb (GObject *gobject,
                             GParamSpec *pspec,
                             source_widgets *widgets)
{
    gboolean new_editable, old_editable;
    const char *text;

    text = gtk_entry_get_text (GTK_ENTRY (widgets->entry));
    new_editable = (strlen (text) > 0);
    old_editable = GTK_WIDGET_SENSITIVE (widgets->check);
    if (new_editable != old_editable) {
        gtk_widget_set_sensitive (widgets->check, new_editable);
        toggle_set_active (widgets->check, new_editable);
    }
}
