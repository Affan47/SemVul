transaction_changed_confirm(VirtualLocation *p_new_virt_loc,
                            VirtualLocation *virt_loc,
                            SplitRegister *reg, Transaction *new_trans,
                            gboolean exact_traversal)
{
    GtkWidget *dialog, *window;
    gint response;
    const char *title = _("Save the changed transaction?");
    const char *message =
        _("The current transaction has been changed. Would you like to "
          "record the changes before moving to a new transaction, discard the "
          "changes, or return to the changed transaction?");

    window = gnc_split_register_get_parent(reg);
    dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_QUESTION,
                                    GTK_BUTTONS_NONE,
                                    "%s", title);
    gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(dialog),
            "%s", message);
    gtk_dialog_add_buttons(GTK_DIALOG(dialog),
                           _("_Discard Changes"), GTK_RESPONSE_REJECT,
                           GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                           _("_Record Changes"), GTK_RESPONSE_ACCEPT,
                           NULL);
    response = gnc_dialog_run(GTK_DIALOG(dialog), GNC_PREF_WARN_REG_TRANS_MOD);
    gtk_widget_destroy(dialog);

    switch (response)
    {
    case GTK_RESPONSE_ACCEPT:
        break;

    case GTK_RESPONSE_REJECT:
    {
        VirtualCellLocation vcell_loc;
        Split *new_split;
        Split *trans_split;
        CursorClass new_class;

        new_split = gnc_split_register_get_split (reg, virt_loc->vcell_loc);
        trans_split = gnc_split_register_get_trans_split (reg,
                      virt_loc->vcell_loc,
                      NULL);
        new_class = gnc_split_register_get_cursor_class (reg,
                    virt_loc->vcell_loc);

        gnc_split_register_cancel_cursor_trans_changes (reg);

        if (gnc_split_register_find_split (reg, new_trans, trans_split,
                                           new_split, new_class, &vcell_loc))
            virt_loc->vcell_loc = vcell_loc;

        gnc_table_find_close_valid_cell (reg->table, virt_loc,
                                         exact_traversal);

        *p_new_virt_loc = *virt_loc;
    }
    break;

    case GTK_RESPONSE_CANCEL:
    default:
        return TRUE;
    }

    return FALSE;
}
