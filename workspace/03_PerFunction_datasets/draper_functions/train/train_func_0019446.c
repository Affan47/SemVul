gnc_ledger_display_template_gl (char *id)
{
    QofBook *book;
    Query *q;
    GNCLedgerDisplay *ld;
    SplitRegister *sr;
    Account *root, *acct;
    gboolean isTemplateModeTrue;

    ENTER("id=%s", id ? id : "(null)");

    acct = NULL;
    isTemplateModeTrue = TRUE;

    q = qof_query_create_for(GNC_ID_SPLIT);

    book = gnc_get_current_book ();
    qof_query_set_book (q, book);

    if ( id != NULL )
    {
        root = gnc_book_get_template_root (book);
        acct = gnc_account_lookup_by_name(root, id);
        g_assert( acct );
        xaccQueryAddSingleAccountMatch (q, acct, QOF_QUERY_AND);
    }

    ld = gnc_ledger_display_internal (NULL, q, LD_GL,
                                      SEARCH_LEDGER,
                                      REG_STYLE_JOURNAL,
                                      FALSE,
                                      isTemplateModeTrue);

    sr = gnc_ledger_display_get_split_register (ld);
    if ( acct )
    {
        gnc_split_register_set_template_account (sr, acct);
    }

    LEAVE("%p", ld);
    return ld;
}
