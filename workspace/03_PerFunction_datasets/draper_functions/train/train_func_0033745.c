gnc_commodity_find_currency (QofBook *book, xmlNodePtr tree)
{
    gnc_commodity_table * table;
    gnc_commodity *currency = NULL;
    gchar *exchange = NULL, *mnemonic = NULL;
    xmlNodePtr node;

    for (node = tree->xmlChildrenNode; node; node = node->next)
    {
        if (g_strcmp0((char*) node->name, cmdty_namespace) == 0)
            exchange = (gchar*) xmlNodeGetContent (node->xmlChildrenNode);
        if (g_strcmp0((char*) node->name, cmdty_id) == 0)
            mnemonic = (gchar*) xmlNodeGetContent (node->xmlChildrenNode);
    }

    if (exchange
            && gnc_commodity_namespace_is_iso(exchange)
            && mnemonic)
    {
        table = gnc_commodity_table_get_table(book);
        currency = gnc_commodity_table_lookup(table, exchange, mnemonic);
    }

    if (exchange)
        xmlFree(exchange);
    if (mnemonic)
        xmlFree(mnemonic);

    return currency;
}
