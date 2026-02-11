gnc_account_window_set_name (AccountWindow *aw)
{
    char *fullname;
    char *title;

    if (!aw || !aw->parent_tree)
        return;

    fullname = get_ui_fullname (aw);

    if (aw->dialog_type == EDIT_ACCOUNT)
        title = g_strconcat(_("Edit Account"), " - ", fullname, NULL);
    else if (aw->next_name && (g_strv_length(aw->next_name) > 0))
    {
        const char *format = _("(%d) New Accounts");
        char *prefix;

        prefix = g_strdup_printf (format, g_strv_length(aw->next_name) + 1);

        title = g_strconcat (prefix, " - ", fullname, " ...", NULL);

        g_free (prefix);
    }
    else
        title = g_strconcat (_("New Account"), " - ", fullname, NULL);

    gtk_window_set_title (GTK_WINDOW(aw->dialog), title);

    g_free (fullname);
    g_free (title);
}
