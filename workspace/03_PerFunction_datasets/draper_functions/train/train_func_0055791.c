filter_gui_edit_size_rule(rule_t *r)
{
    filesize_t min     = 0;
    filesize_t max     = 0;
    gpointer target = DEFAULT_TARGET;
    gboolean invert = FALSE;
    gboolean active = TRUE;
    gboolean soft   = FALSE;

    g_assert(r == NULL || r->type == RULE_SIZE);

    if (gui_filter_dialog() == NULL)
        return;

    if (r != NULL) {
        min    = r->u.size.lower;
        max    = r->u.size.upper;
        target = r->target;
        invert = RULE_IS_NEGATED(r);
        active = RULE_IS_ACTIVE(r);
        soft   = RULE_IS_SOFT(r);
    }

    gtk_entry_printf(
        GTK_ENTRY(gui_filter_dialog_lookup("entry_filter_size_min")),
		"%s", uint64_to_string(min));
    gtk_entry_printf(
        GTK_ENTRY(gui_filter_dialog_lookup("entry_filter_size_max")),
		"%s", uint64_to_string(max));
    option_menu_select_item_by_data(GTK_OPTION_MENU(
        	gui_filter_dialog_lookup("optionmenu_filter_size_target")),
        target);
    gtk_toggle_button_set_active(
        GTK_TOGGLE_BUTTON(lookup_widget
            (gui_filter_dialog(), "checkbutton_filter_size_invert_cond")),
        invert);
    gtk_toggle_button_set_active(
        GTK_TOGGLE_BUTTON
            (gui_filter_dialog_lookup("checkbutton_filter_size_active")),
        active);
    gtk_toggle_button_set_active(
        GTK_TOGGLE_BUTTON
            (gui_filter_dialog_lookup("checkbutton_filter_size_soft")),
        soft);

    gtk_notebook_set_current_page(
        GTK_NOTEBOOK(gui_filter_dialog_lookup("notebook_filter_detail")),
        nb_filt_page_size);
}
