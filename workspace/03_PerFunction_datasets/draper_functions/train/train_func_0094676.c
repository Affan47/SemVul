gnc_is_euro_currency(const gnc_commodity * currency)
{
    gnc_euro_rate_struct *result;

    if (currency == NULL)
        return FALSE;

    if (!gnc_commodity_is_iso(currency))
        return FALSE;

    result = bsearch(currency,
                     gnc_euro_rates,
                     sizeof(gnc_euro_rates) / sizeof(gnc_euro_rate_struct),
                     sizeof(gnc_euro_rate_struct),
                     gnc_euro_rate_compare);

    if (result == NULL)
        return FALSE;

    return TRUE;
}
