test_instance_get_set_dirty( Fixture *fixture, gconstpointer pData )
{
    QofIdType type = "test type";
    QofCollection *col;


    col = qof_collection_new ( type );
    qof_instance_set_collection( fixture->inst, col );
    g_assert( qof_instance_get_collection( fixture->inst ) );

    g_test_message( "Test get_dirty on empty instance returns false" );
    g_assert( qof_instance_get_dirty( NULL ) == FALSE );

    g_test_message( "Test dirty in normal mode" );
    g_assert( !qof_get_alt_dirty_mode() );
    g_assert( !qof_instance_get_dirty_flag( fixture->inst ) );
    g_assert( !qof_collection_is_dirty( col ) );
    g_assert( !qof_instance_get_dirty( fixture->inst ) );
    qof_instance_set_dirty( fixture->inst );
    g_assert( qof_instance_get_dirty_flag( fixture->inst ) );
    g_assert( qof_collection_is_dirty( col ) );
    g_assert( qof_instance_get_dirty( fixture->inst ) );


    g_test_message( "Test dirty in alternate mode" );
    qof_set_alt_dirty_mode ( TRUE );

    qof_collection_mark_clean( col );
    qof_instance_set_dirty_flag( fixture->inst, FALSE );

    g_assert( qof_get_alt_dirty_mode() );
    g_assert( !qof_instance_get_dirty_flag( fixture->inst ) );
    g_assert( !qof_collection_is_dirty( col ) );
    g_assert( !qof_instance_get_dirty( fixture->inst ) );
    qof_instance_set_dirty( fixture->inst );
    g_assert( qof_instance_get_dirty_flag( fixture->inst ) );
    g_assert( !qof_collection_is_dirty( col ) );
    g_assert( qof_instance_get_dirty( fixture->inst ) );


    qof_instance_set_collection( fixture->inst, NULL );
    qof_collection_destroy( col );
}
