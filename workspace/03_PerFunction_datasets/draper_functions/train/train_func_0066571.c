filter_gui_get_state_rule(void)
{
    filter_t *target;
    enum filter_prop_state display  = FILTER_PROP_STATE_IGNORE;
    enum filter_prop_state download = FILTER_PROP_STATE_IGNORE;
    gboolean active;
    gboolean soft;
    gboolean negate;
    guint16 flags;
    GtkWidget *act;

    if (gui_filter_dialog() == NULL)
        return NULL;

    target = option_menu_get_selected_data(GTK_OPTION_MENU(
			gui_filter_dialog_lookup("optionmenu_filter_state_target")));

    act = radiobutton_get_active_in_group
        (GTK_RADIO_BUTTON(lookup_widget
            (gui_filter_dialog(), "radiobutton_filter_state_display_do")));
    display = (enum filter_prop_state)
        GPOINTER_TO_UINT(gtk_object_get_user_data(GTK_OBJECT(act)));

    act = radiobutton_get_active_in_group
        (GTK_RADIO_BUTTON(lookup_widget
            (gui_filter_dialog(), "radiobutton_filter_state_download_do")));
    download = (enum filter_prop_state)
        GPOINTER_TO_UINT(gtk_object_get_user_data(GTK_OBJECT(act)));

    active = gtk_toggle_button_get_active
        (GTK_TOGGLE_BUTTON(lookup_widget
            (gui_filter_dialog(), "checkbutton_filter_state_active")));

    soft = gtk_toggle_button_get_active
        (GTK_TOGGLE_BUTTON(lookup_widget
            (gui_filter_dialog(), "checkbutton_filter_state_soft")));

    negate = gtk_toggle_button_get_active
        (GTK_TOGGLE_BUTTON(lookup_widget
            (gui_filter_dialog(), "checkbutton_filter_state_invert_cond")));

    flags = (active ? RULE_FLAG_ACTIVE : 0) |
            (soft   ? RULE_FLAG_SOFT   : 0) |
            (negate ? RULE_FLAG_NEGATE : 0);

    return filter_new_state_rule(display, download, target, flags);
}
