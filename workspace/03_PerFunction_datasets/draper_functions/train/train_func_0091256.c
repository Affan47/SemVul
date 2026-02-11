test_book_mark_session_dirty( Fixture *fixture, gconstpointer pData )
{
    QofBook *_empty = NULL;
    time64 before, after;
    guint param = (guint) g_test_rand_int();

    g_test_message( "Testing when book is NULL" );
    qof_book_mark_session_dirty( _empty );
    g_assert( _empty == NULL );

    g_test_message( "Testing when book is not dirty and dirty_cb is null" );
    g_assert_cmpint( qof_book_get_session_dirty_time( fixture->book ), == , 0);
    g_assert( fixture->book->dirty_cb == NULL );
    g_assert( qof_book_session_not_saved( fixture->book ) == FALSE );
    before = gnc_time (NULL);
    qof_book_mark_session_dirty( fixture->book );
    after = gnc_time (NULL);
    g_assert_cmpint( qof_book_get_session_dirty_time( fixture->book ), >= , before);
    g_assert_cmpint( qof_book_get_session_dirty_time( fixture->book ), <= , after);
    g_assert( qof_book_session_not_saved( fixture->book ) == TRUE );

    g_test_message( "Testing when book is not dirty and dirty_cb is not null" );

    qof_book_mark_session_saved( fixture->book );
    qof_book_set_dirty_cb( fixture->book, mock_dirty_cb, (gpointer) (&param) );
    test_struct.data = (gpointer) (&param);
    test_struct.called = FALSE;
    g_assert( fixture->book->dirty_cb != NULL );
    g_assert_cmpint( qof_book_get_session_dirty_time( fixture->book ), == , 0);
    g_assert( qof_book_session_not_saved( fixture->book ) == FALSE );

    before = gnc_time (NULL);
    qof_book_mark_session_dirty( fixture->book );
    after = gnc_time (NULL);

    g_assert_cmpint( qof_book_get_session_dirty_time( fixture->book ), >= , before);
    g_assert_cmpint( qof_book_get_session_dirty_time( fixture->book ), <= , after);
    g_assert( qof_book_session_not_saved( fixture->book ) == TRUE );
    g_assert( test_struct.called );

    g_test_message( "Testing when book is dirty" );
    g_assert( qof_book_session_not_saved( fixture->book ) == TRUE );
    before = qof_book_get_session_dirty_time( fixture->book );
    qof_book_mark_session_dirty( fixture->book );
    g_assert( qof_book_session_not_saved( fixture->book ) == TRUE );
    after = qof_book_get_session_dirty_time( fixture->book );
    g_assert_cmpint( before, == , after );
}
