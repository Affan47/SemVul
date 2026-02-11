fm_path_entry_key_press(GtkWidget   *widget, GdkEventKey *event, gpointer user_data)
{
    FmPathEntry *entry = FM_PATH_ENTRY(widget);
    FmPathEntryPrivate *priv  = FM_PATH_ENTRY_GET_PRIVATE(entry);
    GdkModifierType state;

    if(gtk_get_current_event_state(&state) &&
       (state & GDK_CONTROL_MASK) == GDK_CONTROL_MASK)
        return FALSE;

    switch( event->keyval )
    {
    case GDK_KEY_Tab:
        {
#if 0
            gtk_editable_get_selection_bounds(editable, &start, &end);
            if(start != end)
                gtk_editable_set_position(editable, MAX(start, end));
            else
                start_explicit_completion(entry);
#endif
            gtk_entry_completion_insert_prefix(priv->completion);
            gtk_editable_set_position(GTK_EDITABLE(entry), -1);
            if (_path_entry_is_single_match(entry, priv))
            {
                int pos = gtk_editable_get_position(GTK_EDITABLE(entry));
                gtk_editable_insert_text(GTK_EDITABLE(entry), "/", 1, &pos);
                gtk_editable_set_position(GTK_EDITABLE(entry), pos);
            }
            return TRUE;
        }
    }
    return FALSE;
}
