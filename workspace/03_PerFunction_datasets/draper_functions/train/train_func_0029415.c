test_qof_object_register( Fixture *fixture, gconstpointer pData )
{
    GList *books = NULL;
    gint32 list_length = g_test_rand_int_range( 0, 5 );
    int i;
    QofObject *simple_object = NULL;

    for (i = 0; i < list_length; i++ )
    {
        QofBook *book = qof_book_new();
        g_assert( book );
        books = g_list_prepend ( books, book );
        g_assert_cmpint( g_list_length( books ), == , (i + 1) );
    }
    g_assert_cmpint( list_length, == , g_list_length( books ) );

    g_test_message( "Test null check" );
    g_assert( qof_object_register( NULL ) == FALSE );

    g_test_message( "Test new object register with book_begin specified" );
    fixture->qofobject->book_begin = mock_book_begin;
    book_begin_struct.books = books;
    book_begin_struct.call_count = 0;
    g_assert( qof_object_register( fixture->qofobject ) == TRUE );
    g_assert( qof_object_lookup( "my type object" ) == fixture->qofobject );
    g_assert_cmpint( book_begin_struct.call_count, == , list_length );

    g_test_message( "Test registering the same object one more time" );
    book_begin_struct.call_count = 0;
    g_assert( qof_object_register( fixture->qofobject ) == FALSE );
    g_assert( qof_object_lookup( "my type object" ) == fixture->qofobject );
    g_assert_cmpint( book_begin_struct.call_count, == , 0 );

    g_test_message( "Test new object register without book_begin specified" );
    simple_object = new_object( "my type simple", "simple desc", EMPTY );
    g_assert( qof_object_register( simple_object ) == TRUE );
    g_assert( qof_object_lookup( "my type simple" ) == simple_object );
    g_assert_cmpint( book_begin_struct.call_count, == , 0 );

    g_test_message( "Test register simple object one more time" );
    g_assert( qof_object_register( simple_object ) == FALSE );
    g_assert( qof_object_lookup( "my type simple" ) == simple_object );

    g_test_message( "Test book begin is called only one time when object is registered" );
    simple_object->book_begin = mock_book_begin;
    book_begin_struct.books = books;
    book_begin_struct.call_count = 0;
    g_assert( qof_object_register( simple_object ) == FALSE );
    g_assert_cmpint( book_begin_struct.call_count, == , 0 );

    g_list_foreach( books, (GFunc) qof_book_destroy, NULL );
    g_list_free( books );
    g_free( simple_object );
}
