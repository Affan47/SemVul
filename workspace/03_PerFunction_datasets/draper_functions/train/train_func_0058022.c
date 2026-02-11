refresh_details_page (StockSplitInfo *info)
{
    GNCPrintAmountInfo print_info;
    gnc_commodity *commodity, *currency;
    Account *account;
    QofBook *book;
    GNCPriceDB *db;
    GList *prices;

    account = info->acct;

    g_return_if_fail (account != NULL);

    print_info = gnc_account_print_info (account, FALSE);

    gnc_amount_edit_set_print_info (GNC_AMOUNT_EDIT (info->distribution_edit),
                                    print_info);
    gnc_amount_edit_set_fraction (GNC_AMOUNT_EDIT (info->distribution_edit),
                                  xaccAccountGetCommoditySCU (account));

    commodity = xaccAccountGetCommodity (account);
    book = gnc_account_get_book (account);
    db = gnc_pricedb_get_db(book);

    prices = gnc_pricedb_lookup_latest_any_currency(db, commodity);
    if (prices)
    {

        currency = gnc_price_get_currency(prices->data);
    }
    else
    {

        currency = gnc_default_currency ();
    }
    gnc_price_list_destroy(prices);

    gnc_currency_edit_set_currency
    (GNC_CURRENCY_EDIT (info->price_currency_edit),
     currency);
}
