swap_delete_keybinding_changed_callback (gpointer callback_data)
{
    NemoView *view = NEMO_VIEW (callback_data);

    GtkBindingSet *binding_set = gtk_binding_set_find ("NemoView");

    gboolean swap_keys = g_settings_get_boolean (nemo_preferences, NEMO_PREFERENCES_SWAP_TRASH_DELETE);

    gtk_binding_entry_remove (binding_set, GDK_KEY_Delete, 0);
    gtk_binding_entry_remove (binding_set, GDK_KEY_KP_Delete, 0);
    gtk_binding_entry_remove (binding_set, GDK_KEY_KP_Delete, GDK_SHIFT_MASK);
    gtk_binding_entry_remove (binding_set, GDK_KEY_Delete, GDK_SHIFT_MASK);

    if (swap_keys) {
        gtk_binding_entry_add_signal (binding_set, GDK_KEY_Delete, 0,
                          "delete", 0);
        gtk_binding_entry_add_signal (binding_set, GDK_KEY_KP_Delete, 0,
                          "delete", 0);
        gtk_binding_entry_add_signal (binding_set, GDK_KEY_KP_Delete, GDK_SHIFT_MASK,
                          "trash", 0);
        gtk_binding_entry_add_signal (binding_set, GDK_KEY_Delete, GDK_SHIFT_MASK,
                          "trash", 0);
    } else {
        gtk_binding_entry_add_signal (binding_set, GDK_KEY_Delete, 0,
                          "trash", 0);
        gtk_binding_entry_add_signal (binding_set, GDK_KEY_KP_Delete, 0,
                          "trash", 0);
        gtk_binding_entry_add_signal (binding_set, GDK_KEY_KP_Delete, GDK_SHIFT_MASK,
                          "delete", 0);
        gtk_binding_entry_add_signal (binding_set, GDK_KEY_Delete, GDK_SHIFT_MASK,
                          "delete", 0);
    }
}
