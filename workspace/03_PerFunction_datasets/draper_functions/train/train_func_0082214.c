get_random_commodity (QofBook *book)
{
    gnc_commodity *ret;
    gchar *name;
    const gchar *space;
    gchar *mn;
    gchar *cusip;
    int ran_int;
    gnc_commodity_table *table;

    table = gnc_commodity_table_get_table (book);

#if 0
    if (table &&
            (gnc_commodity_table_get_size (table) > 0) &&
            get_random_int_in_range (1, 5) < 5)
        return get_random_commodity_from_table (table);
#endif

    mn = get_random_string_length_in_range(1, 3);
    space = get_random_commodity_namespace();

    if (table)
    {
        ret = gnc_commodity_table_lookup (table, space, mn);

        if (ret)
        {
            g_free (mn);
            return ret;
        }
    }

    name = get_random_string();
    cusip = get_random_string();

    ran_int = get_random_int_in_range(min_scu, max_scu);

    ret = gnc_commodity_new(book, name, space, mn, cusip, ran_int);

    g_free(mn);
    g_free(name);
    g_free(cusip);

    if (table)
        ret = gnc_commodity_table_insert (table, ret);

    return ret;
}
