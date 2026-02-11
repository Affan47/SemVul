_gncBillTermDestroy (QofBook *book)
{
    struct _book_info *bi;

    if (!book) return;

    bi = qof_book_get_data (book, _GNC_MOD_NAME);

    g_list_free (bi->terms);
    g_free (bi);
}
