gnc_split_register_balance_trans (SplitRegister *reg, Transaction *trans)
{
    int choice;
    int default_value;
    Account *default_account;
    Account *other_account;
    Account *root;
    GList *radio_list = NULL;
    const char *title   = _("Rebalance Transaction");
    const char *message = _("The current transaction is not balanced.");
    Split *split;
    Split *other_split;
    gboolean two_accounts;
    gboolean multi_currency;


    if (xaccTransIsBalanced (trans))
        return FALSE;

    if (xaccTransUseTradingAccounts (trans))
    {
        MonetaryList *imbal_list;
        gnc_monetary *imbal_mon;
        imbal_list = xaccTransGetImbalance (trans);


        if (!imbal_list)


            multi_currency = TRUE;
        else
        {
            imbal_mon = imbal_list->data;
            if (!imbal_list->next &&
                    gnc_commodity_equiv(gnc_monetary_commodity(*imbal_mon),
                                        xaccTransGetCurrency(trans)))
                multi_currency = FALSE;
            else
                multi_currency = TRUE;
        }


        gnc_monetary_list_free(imbal_list);
    }
    else
        multi_currency = FALSE;

    split = xaccTransGetSplit (trans, 0);
    other_split = xaccSplitGetOtherSplit (split);

    if (other_split == NULL)
    {

        split = xaccTransGetSplit (trans, 1);
        if (split) other_split = xaccSplitGetOtherSplit (split);
        else split = xaccTransGetSplit (trans, 0);
    }
    if (other_split == NULL || multi_currency)
    {
        two_accounts = FALSE;
        other_account = NULL;
    }
    else
    {
        two_accounts = TRUE;
        other_account = xaccSplitGetAccount (other_split);
    }

    default_account = gnc_split_register_get_default_account (reg);


    if (default_account == other_account)
        other_account = xaccSplitGetAccount (split);


    if (default_account == other_account)
        two_accounts = FALSE;

    radio_list = g_list_append (radio_list,
                                _("Balance it _manually"));
    radio_list = g_list_append (radio_list,
                                _("Let GnuCash _add an adjusting split"));

    if (reg->type < NUM_SINGLE_REGISTER_TYPES && !multi_currency)
    {
        radio_list = g_list_append (radio_list,
                                    _("Adjust current account _split total"));

        default_value = 2;
        if (two_accounts)
        {
            radio_list = g_list_append (radio_list,
                                        _("Adjust _other account split total"));
            default_value = 3;
        }
    }
    else
        default_value = 0;

    choice = gnc_choose_radio_option_dialog
             (gnc_split_register_get_parent (reg),
              title,
              message,
              _("_Rebalance"),
              default_value,
              radio_list);

    g_list_free (radio_list);

    root = gnc_account_get_root(default_account);
    switch (choice)
    {
    default:
    case 0:
        break;

    case 1:
        xaccTransScrubImbalance (trans, root, NULL);
        break;

    case 2:
        xaccTransScrubImbalance (trans, root, default_account);
        break;

    case 3:
        xaccTransScrubImbalance (trans, root, other_account);
        break;
    }

    return TRUE;
}
