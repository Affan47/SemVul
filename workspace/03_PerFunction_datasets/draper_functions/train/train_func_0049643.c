write_book(FILE *out, QofBook *book, sixtp_gdv2 *gd)
{
    struct file_backend be_data;

#ifdef IMPLEMENT_BOOK_DOM_TREES_LATER


    xmlNodePtr node;

    node = gnc_book_dom_tree_create(book);

    if (!node)
    {
        return FALSE;
    }

    xmlElemDump(out, NULL, node);
    xmlFreeNode(node);

    if (ferror(out) || fprintf(out, "\n") < 0)
    {
        return FALSE;
    }

#endif

    be_data.out = out;
    be_data.book = book;
    be_data.gd = gd;
    if (fprintf( out, "<%s version=\"%s\">\n", BOOK_TAG, gnc_v2_book_version_string) < 0)
        return FALSE;
    if (!write_book_parts (out, book))
        return FALSE;


    if (!write_counts(out,
                      "commodity",
                      gnc_commodity_table_get_size(
                          gnc_commodity_table_get_table(book)),
                      "account",
                      1 + gnc_account_n_descendants(gnc_book_get_root_account(book)),
                      "transaction",
                      gnc_book_count_transactions(book),
                      "schedxaction",
                      g_list_length(gnc_book_get_schedxactions(book)->sx_list),
                      "budget", qof_collection_count(
                          qof_book_get_collection(book, GNC_ID_BUDGET)),
                      "price", gnc_pricedb_get_num_prices(gnc_pricedb_get_db(book)),
                      NULL))
        return FALSE;

    qof_object_foreach_backend (GNC_FILE_BACKEND, write_counts_cb, &be_data);

    if (ferror(out)
            || !write_commodities(out, book, gd)
            || !write_pricedb(out, book, gd)
            || !write_accounts(out, book, gd)
            || !write_transactions(out, book, gd)
            || !write_template_transaction_data(out, book, gd)
            || !write_schedXactions(out, book, gd))

        return FALSE;

    qof_collection_foreach(qof_book_get_collection(book, GNC_ID_BUDGET),
                           write_budget, &be_data);
    if (ferror(out))
        return FALSE;

    qof_object_foreach_backend (GNC_FILE_BACKEND, write_data_cb, &be_data);
    if (ferror(out))
        return FALSE;

    if (fprintf( out, "</%s>\n", BOOK_TAG ) < 0)
        return FALSE;

    return TRUE;
}
