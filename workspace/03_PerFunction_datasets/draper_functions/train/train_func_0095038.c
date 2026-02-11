xaccAccountFindLatestOpenLot (Account *acc, gnc_numeric sign,
                              gnc_commodity *currency)
{
    GNCLot *lot;
    ENTER (" sign=%" G_GINT64_FORMAT "/%" G_GINT64_FORMAT,
           sign.num, sign.denom);

    lot = xaccAccountFindOpenLot (acc, sign, currency,
                                  G_MININT64, latest_pred);
    LEAVE ("found lot=%p %s", lot, gnc_lot_get_title (lot));
    return lot;
}
