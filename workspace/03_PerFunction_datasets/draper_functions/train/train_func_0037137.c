_ufarray_entry_changed(GtkWidget *entry, GdkEventFocus *event,
                                       UFObject *object)
    {
        if (event->in)
            return false;
        UFArray &array = *object;
        array.Set(gtk_entry_get_text(GTK_ENTRY(entry)));
        _ufobject_reset_button_state(object);
        return false;
    }
