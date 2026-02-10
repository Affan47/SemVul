gnc_tree_control_split_reg_get_account_by_name (GncTreeViewSplitReg *view, const char *name)
{
    GtkWidget *window;
    const char *placeholder = _("The account %s does not allow transactions.");
    const char *missing = _("The account %s does not exist. "
                            "Would you like to create it?");
    char *account_name;
    Account *account;

    if (!name || (strlen(name) == 0))
        return NULL;


    if (gnc_prefs_get_bool (GNC_PREFS_GROUP_GENERAL_REGISTER, GNC_PREF_SHOW_LEAF_ACCT_NAMES))
        account = gnc_account_lookup_by_name (gnc_get_current_root_account(), name);
    else
        account = gnc_account_lookup_by_full_name (gnc_get_current_root_account(), name);

    if (!account)
        account = gnc_account_lookup_by_code (gnc_get_current_root_account(), name);

    window = gnc_tree_view_split_reg_get_parent (view);

    if (!account)
    {

        if (!gnc_verify_dialog (window, TRUE, missing, name))
            return NULL;


        account = gnc_ui_new_accounts_from_name_window (name);
        if (!account)
            return NULL;
    }


    if (xaccAccountGetPlaceholder (account))
        gnc_error_dialog (window, placeholder, name);


    return account;
}
