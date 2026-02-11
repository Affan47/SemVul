qof_book_set_data_fin (QofBook *book, const char *key, gpointer data, QofBookFinalCB cb)
{
    if (!book || !key) return;
    g_hash_table_insert (book->data_tables, (gpointer)key, data);

    if (!cb) return;
    g_hash_table_insert (book->data_table_finalizers, (gpointer)key, cb);
}
