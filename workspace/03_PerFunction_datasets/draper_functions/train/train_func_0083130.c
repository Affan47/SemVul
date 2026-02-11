gnc_account_commodity_from_type (AccountWindow * aw, gboolean update)
{
    dialog_commodity_mode new_mode;

    if (aw->type == ACCT_TYPE_TRADING)
        new_mode = DIAG_COMM_ALL;
    else if ((aw->type == ACCT_TYPE_STOCK) || (aw->type == ACCT_TYPE_MUTUAL))
        new_mode = DIAG_COMM_NON_CURRENCY;
    else
        new_mode = DIAG_COMM_CURRENCY;

    if (update && (new_mode != aw->commodity_mode))
    {
        gnc_general_select_set_selected(GNC_GENERAL_SELECT (aw->commodity_edit),
                                        NULL);
    }

    aw->commodity_mode = new_mode;
}
