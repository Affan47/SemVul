on_keybinding_entry_key_key_press_event(GtkWidget       *widget,
                                        GdkEventKey     *event,
                                        gpointer         user_data)
{
    gtk_entry_set_text(
        GTK_ENTRY(keybinding_entry_key), gdk_keyval_name(event->keyval));


    if (event->state & GDK_CONTROL_MASK)
        gtk_toggle_button_set_active(
            GTK_TOGGLE_BUTTON(keybinding_checkbutton_control), TRUE);

#if 0
    else
        gtk_toggle_button_set_active(
            GTK_TOGGLE_BUTTON(keybinding_checkbutton_control), FALSE);
#endif

    if (event->state & GDK_SHIFT_MASK)
        gtk_toggle_button_set_active(
            GTK_TOGGLE_BUTTON(keybinding_checkbutton_shift), TRUE);

#if 0
    else
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(keybinding_checkbutton_shift), FALSE);


    gtk_toggle_button_set_active(
        GTK_TOGGLE_BUTTON(keybinding_checkbutton_alt), FALSE);
    gtk_toggle_button_set_active(
        GTK_TOGGLE_BUTTON(keybinding_checkbutton_meta), FALSE);
#endif


    return TRUE;
}
