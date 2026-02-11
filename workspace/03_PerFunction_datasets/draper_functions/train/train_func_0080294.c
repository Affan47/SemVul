find_trading_split (Transaction *trans, Account *root,
                    gnc_commodity *commodity)
{
    Account *trading_account;
    Account *ns_account;
    Account *account;

    if (!root)
    {
        root = gnc_book_get_root_account (xaccTransGetBook (trans));
        if (NULL == root)
        {

            PERR ("Bad data corruption, no root account in book");
            return NULL;
        }
    }

    trading_account = gnc_account_lookup_by_name (root, _("Trading"));
    if (!trading_account)
    {
        return NULL;
    }

    ns_account = gnc_account_lookup_by_name (trading_account,
                 gnc_commodity_get_namespace(commodity));
    if (!ns_account)
    {
        return NULL;
    }

    account = gnc_account_lookup_by_name (ns_account,
                                          gnc_commodity_get_mnemonic(commodity));
    if (!account)
    {
        return NULL;
    }

    return xaccTransFindSplitByAccount(trans, account);
}
