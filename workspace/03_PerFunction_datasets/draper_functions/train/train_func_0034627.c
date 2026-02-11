gnc_get_shared_entry_desc_quickfill (QofBook *book,
        const char * key, gboolean use_invoices)
{
    EntryQF *qfb;

    g_assert(book);
    g_assert(key);

    qfb = qof_book_get_data (book, key);

    if (!qfb)
    {
        qfb = build_shared_quickfill(book, key, use_invoices);
    }

    g_assert(use_invoices == qfb->using_invoices);
    return qfb->qf;
}
