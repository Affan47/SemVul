add_account_local(sixtp_gdv2 *data, Account *act)
{
    gnc_commodity_table *table;
    Account *parent, *root;
    int type;

    table = gnc_commodity_table_get_table (data->book);

    clear_up_account_commodity(table, act,
                               DxaccAccountGetCurrency,
                               DxaccAccountSetCurrency,
                               NULL, NULL);

    clear_up_account_commodity(table, act,
                               xaccAccountGetCommodity,
                               xaccAccountSetCommodity,
                               xaccAccountGetCommoditySCUi,
                               xaccAccountSetCommoditySCU);

    xaccAccountScrubCommodity (act);
    xaccAccountScrubKvp (act);


    type = xaccAccountGetType(act);
    if (type == ACCT_TYPE_ROOT)
    {
        gnc_book_set_root_account(data->book, act);
    }
    else
    {
        parent = gnc_account_get_parent(act);
        if (parent == NULL)
        {
            root = gnc_book_get_root_account(data->book);
            gnc_account_append_child(root, act);
        }
    }

    data->counter.accounts_loaded++;
    run_callback(data, "account");

    return FALSE;
}
