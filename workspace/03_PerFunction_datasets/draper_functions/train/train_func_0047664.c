GetOrMakeLotOrphanAccount (Account *root, gnc_commodity * currency)
{
    char * accname;
    Account * acc;

    g_return_val_if_fail (root, NULL);


    if (!currency)
    {
        PERR ("No currency specified!");
        return NULL;
    }

    accname = g_strconcat (_("Orphaned Gains"), "-",
                           gnc_commodity_get_mnemonic (currency), NULL);


    acc = gnc_account_lookup_by_name(root, accname);

    if (acc == NULL)
    {

        acc = xaccMallocAccount (gnc_account_get_book(root));
        xaccAccountBeginEdit (acc);
        xaccAccountSetName (acc, accname);
        xaccAccountSetCommodity (acc, currency);
        xaccAccountSetType (acc, ACCT_TYPE_INCOME);
        xaccAccountSetDescription (acc, _("Realized Gain/Loss"));
        xaccAccountSetNotes (acc,
                             _("Realized Gains or Losses from "
                               "Commodity or Trading Accounts "
                               "that haven't been recorded elsewhere."));


        gnc_account_append_child (root, acc);
        xaccAccountCommitEdit (acc);
    }

    g_free (accname);

    return acc;
}
