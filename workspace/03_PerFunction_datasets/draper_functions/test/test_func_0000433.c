autosave_remove_timer_cb(QofBook *book, gpointer key, gpointer user_data)
{
    guint autosave_source_id = GPOINTER_TO_UINT(user_data);
    gboolean res;

    if (autosave_source_id > 0)
    {
        res = g_source_remove (autosave_source_id);
        g_debug("Removing auto save timer with id %d, result=%s\n",
                autosave_source_id, (res ? "TRUE" : "FALSE"));


        qof_book_set_data_fin(book, AUTOSAVE_SOURCE_ID,
                              GUINT_TO_POINTER(0), autosave_remove_timer_cb);
    }
}
