gnc_pricedb_lookup_at_time(GNCPriceDB *db,
                           const gnc_commodity *c,
                           const gnc_commodity *currency,
                           Timespec t)
{
    GList *price_list;
    GList *result = NULL;
    GList *item = NULL;
    GHashTable *currency_hash;
    QofBook *book;
    QofBackend *be;

    if (!db || !c || !currency) return NULL;
    ENTER ("db=%p commodity=%p currency=%p", db, c, currency);
    book = qof_instance_get_book(&db->inst);
    be = qof_book_get_backend(book);
#ifdef GNUCASH_MAJOR_VERSION
    if (be && be->price_lookup)
    {
        GNCPriceLookup pl;
        pl.type = LOOKUP_AT_TIME;
        pl.prdb = db;
        pl.commodity = c;
        pl.currency = currency;
        pl.date = t;
        (be->price_lookup) (be, &pl);
    }
#endif
    currency_hash = g_hash_table_lookup(db->commodity_hash, c);
    if (!currency_hash)
    {
        LEAVE (" no currency hash");
        return NULL;
    }

    price_list = g_hash_table_lookup(currency_hash, currency);
    if (!price_list)
    {
        LEAVE (" no price list");
        return NULL;
    }

    item = price_list;
    while (item)
    {
        GNCPrice *p = item->data;
        Timespec price_time = gnc_price_get_time(p);
        if (timespec_equal(&price_time, &t))
        {
            result = g_list_prepend(result, p);
            gnc_price_ref(p);
        }
        item = item->next;
    }
    LEAVE (" ");
    return result;
}
