test_book_kvp_changed( Fixture *fixture, gconstpointer pData )
{
    g_test_message( "Testing book is marked dirty after kvp_changed" );
    g_assert( !qof_instance_is_dirty (QOF_INSTANCE (fixture->book)) );
    qof_book_kvp_changed( fixture->book );
    g_assert( qof_instance_is_dirty (QOF_INSTANCE (fixture->book)) );
}
