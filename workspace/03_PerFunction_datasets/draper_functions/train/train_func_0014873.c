dh_book_manager_update (DhBookManager *book_manager)
{
        DhBookManagerPriv *priv;
        GSList *books_disabled = NULL;
        GList  *l;

        g_return_if_fail (book_manager);

        priv = GET_PRIVATE (book_manager);


        for (l = priv->books; l; l = g_list_next (l)) {
                DhBook *book = DH_BOOK (l->data);

                if (!dh_book_get_enabled (book)) {
                        books_disabled = g_slist_append (books_disabled,
                                                         g_strdup (dh_book_get_name (book)));
                }
        }


        dh_util_state_store_books_disabled (books_disabled);


        g_signal_emit (book_manager,
                       signals[DISABLED_BOOK_LIST_UPDATED],
                       0);

        book_manager_clean_list_of_books_disabled (books_disabled);
}
