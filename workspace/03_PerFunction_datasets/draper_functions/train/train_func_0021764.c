csv_export_info_acct_type_cb (GtkWidget *w, gpointer user_data)
{
    CsvExportInfo *info = user_data;
    const gchar *button_name;

    if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (w)))
    {
        button_name = gtk_buildable_get_name(GTK_BUILDABLE(w));
        if (g_strcmp0 (button_name, "income_radio") == 0)
            info->csva.account_type = ACCT_TYPE_INCOME;
        else if (g_strcmp0 (button_name, "expense_radio") == 0)
            info->csva.account_type = ACCT_TYPE_EXPENSE;
        else if (g_strcmp0 (button_name, "asset_radio") == 0)
            info->csva.account_type = ACCT_TYPE_ASSET;
        else if (g_strcmp0 (button_name, "liab_eq_radio") == 0)
            info->csva.account_type = ACCT_TYPE_LIABILITY;
        else
            return;

        show_acct_type_accounts (info);
        gnc_tree_view_account_refilter
        (GNC_TREE_VIEW_ACCOUNT (info->csva.account_treeview));
        update_accounts_tree (info);
    }
    else
        return;
}
