get_root_account_guid( gpointer pObject )
{
    QofBook* book = QOF_BOOK(pObject);
    const Account* root;

    g_return_val_if_fail( pObject != NULL, NULL );
    g_return_val_if_fail( QOF_IS_BOOK(pObject), NULL );

    root = gnc_book_get_root_account( book );
    return (gpointer)qof_instance_get_guid( QOF_INSTANCE(root) );
}
