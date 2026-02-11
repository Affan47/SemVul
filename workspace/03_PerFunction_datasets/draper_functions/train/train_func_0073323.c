gnc_pricedb_lookup_latest_any_currency(GNCPriceDB *db,
                                       const gnc_commodity *commodity)
{
    GList *result;
    GHashTable *currency_hash;
    QofBook *book;
    QofBackend *be;

    result = NULL;

    if (!db || !commodity) return NULL;
    ENTER ("db=%p commodity=%p", db, commodity);
    book = qof_instance_get_book(&db->inst);
    be = qof_book_get_backend(book);
#ifdef GNUCASH_MAJOR_VERSION
    if (be && be->price_lookup)
    {
        GNCPriceLookup pl;
        pl.type = LOOKUP_LATEST;
        pl.prdb = db;
        pl.commodity = commodity;
        pl.currency = NULL;
        (be->price_lookup) (be, &pl);
    }
#endif
    currency_hash = g_hash_table_lookup(db->commodity_hash, commodity);
    if (!currency_hash)
    {
        LEAVE (" no currency hash");
        return NULL;
    }

    g_hash_table_foreach(currency_hash, lookup_latest, &result);

    if (!result)
    {
        LEAVE (" ");
        return NULL;
    }

    result = g_list_sort(result, compare_prices_by_date);

    LEAVE(" ");
    return result;
}
