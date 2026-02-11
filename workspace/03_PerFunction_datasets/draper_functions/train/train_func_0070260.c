compare_prices_by_date(gconstpointer a, gconstpointer b)
{
    Timespec time_a;
    Timespec time_b;
    gint result;

    if (!a && !b) return 0;

    if (!a) return -1;

    time_a = gnc_price_get_time((GNCPrice *) a);
    time_b = gnc_price_get_time((GNCPrice *) b);

    result = -timespec_cmp(&time_a, &time_b);
    if (result) return result;


    return guid_compare (gnc_price_get_guid((GNCPrice *) a),
                         gnc_price_get_guid((GNCPrice *) b));
}
