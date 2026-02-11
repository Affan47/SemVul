gtu_sr_get_rate_from_db (gnc_commodity *from, gnc_commodity *to)
{
    GNCPrice *prc;
    gnc_numeric rate_split;
    gboolean have_rate = FALSE;
    QofBook *book = gnc_get_current_book ();


    prc = gnc_pricedb_lookup_latest (gnc_pricedb_get_db (book), from, to);
    if (prc)
    {
        rate_split = gnc_price_get_value (prc);
        gnc_price_unref (prc);
        have_rate = TRUE;
    }


    if (!have_rate)
    {
        prc = gnc_pricedb_lookup_latest (gnc_pricedb_get_db (book), to, from);
        if (prc)
        {
            rate_split = gnc_numeric_div (gnc_numeric_create (100, 100), gnc_price_get_value (prc),
                                 GNC_DENOM_AUTO, GNC_HOW_DENOM_REDUCE);

            gnc_price_unref (prc);
            have_rate = TRUE;
        }
    }


    if (!have_rate)
        rate_split = gnc_numeric_create (100, 100);

    return rate_split;
}
