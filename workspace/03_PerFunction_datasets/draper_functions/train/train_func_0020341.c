filter_gui_edit_ip_rule(rule_t *r)
{
    gchar *ip;
    gpointer target = DEFAULT_TARGET;
    gboolean invert = FALSE;
    gboolean active = TRUE;
    gboolean soft   = FALSE;

    g_assert(r == NULL || r->type == RULE_IP);

    if (gui_filter_dialog() == NULL)
        return;

    if (r != NULL) {
        ip   = str_cmsg("%s/%u",
					host_addr_to_string(r->u.ip.addr), r->u.ip.cidr);
        target = r->target;
        invert = RULE_IS_NEGATED(r);
        active = RULE_IS_ACTIVE(r);
        soft   = RULE_IS_SOFT(r);
    } else {
		ip = h_strdup("");
	}

    gtk_entry_set_text(
        GTK_ENTRY(gui_filter_dialog_lookup("entry_filter_ip_address")),
        ip);
    option_menu_select_item_by_data(GTK_OPTION_MENU(
			gui_filter_dialog_lookup("optionmenu_filter_ip_target")),
        target);
    gtk_toggle_button_set_active(
        GTK_TOGGLE_BUTTON(lookup_widget
            (gui_filter_dialog(), "checkbutton_filter_ip_invert_cond")),
        invert);
    gtk_toggle_button_set_active(
        GTK_TOGGLE_BUTTON
            (gui_filter_dialog_lookup("checkbutton_filter_ip_active")),
        active);
    gtk_toggle_button_set_active(
        GTK_TOGGLE_BUTTON
            (gui_filter_dialog_lookup("checkbutton_filter_ip_soft")),
        soft);

   	HFREE_NULL(ip);

    gtk_notebook_set_current_page(
        GTK_NOTEBOOK(gui_filter_dialog_lookup("notebook_filter_detail")),
        nb_filt_page_ip);
}
