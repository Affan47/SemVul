build_shared_quickfill (QofBook *book, Account *root, const char * key,
                        AccountBoolCB cb, gpointer data)
{
    QFB *qfb;

    qfb = g_new0(QFB, 1);
    qfb->qf = gnc_quickfill_new ();
    qfb->book = book;
    qfb->root = root;
    qfb->listener = 0;
    qfb->dont_add_cb = cb;
    qfb->dont_add_data = data;
    qfb->load_list_store = TRUE;
    qfb->list_store =
        gtk_list_store_new (NUM_ACCOUNT_COLUMNS, G_TYPE_STRING, G_TYPE_POINTER);

    gnc_prefs_register_cb (GNC_PREFS_GROUP_GENERAL,
                           GNC_PREF_ACCOUNT_SEPARATOR,
                           shared_quickfill_pref_changed,
                           qfb);

    gnc_prefs_register_cb (GNC_PREFS_GROUP_GENERAL_REGISTER,
                           GNC_PREF_SHOW_LEAF_ACCT_NAMES,
                           shared_quickfill_pref_changed,
                           qfb);

    gnc_account_foreach_descendant(root, load_shared_qf_cb, qfb);
    qfb->load_list_store = FALSE;

    qfb->listener =
        qof_event_register_handler (listen_for_account_events, qfb);

    qof_book_set_data_fin (book, key, qfb, shared_quickfill_destroy);

    return qfb;
}
