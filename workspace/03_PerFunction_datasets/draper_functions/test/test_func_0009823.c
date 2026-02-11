test_kvp_frame_compare( Fixture *fixture, gconstpointer pData )
{
    KvpFrame *cmp_frame = NULL;

    cmp_frame = kvp_frame_new();
    g_assert( cmp_frame );

    g_test_message( "Test the same frame is equal with itself" );
    g_assert_cmpint( kvp_frame_compare( fixture->frame, fixture->frame ), == , 0 );

    g_test_message( "Test first frame null second not null" );
    g_assert_cmpint( kvp_frame_compare( NULL, fixture->frame ), == , -1 );

    g_test_message( "Test first frame not null second null" );
    g_assert_cmpint( kvp_frame_compare( fixture->frame, NULL ), == , 1 );

    g_test_message( "Test first frame is empty second not empty" );
    kvp_frame_set_gint64( fixture->frame, "/test/test2", 64 );
    g_assert( !kvp_frame_is_empty( fixture->frame ) );
    g_assert( kvp_frame_is_empty( cmp_frame ) );
    g_assert_cmpint( kvp_frame_compare( cmp_frame, fixture->frame ), == , -1 );

    g_test_message( "Test first frame is not empty second is empty" );
    g_assert_cmpint( kvp_frame_compare( fixture->frame, cmp_frame ), == , 1 );

    g_test_message( "Test when frames are equal" );
    kvp_frame_set_gint64( cmp_frame, "/test/test2", 64 );
    g_assert( !kvp_frame_is_empty( cmp_frame ) );
    g_assert_cmpint( kvp_frame_compare( fixture->frame, cmp_frame ), == , 0 );

    g_test_message( "Test when frames have equal data but second frame has additional slot set" );
    kvp_frame_set_string( fixture->frame, "/test/test3", "abcdefghijklmnop" );
    g_assert_cmpint( kvp_frame_compare( cmp_frame, fixture->frame ), == , -1 );

    g_test_message( "Test when frames have equal data but first frame has additional slot set" );
    g_assert_cmpint( kvp_frame_compare( fixture->frame, cmp_frame ), == , 1 );

    g_test_message( "Test when frames have equal number of slots second frame has different data in one slot" );
    kvp_frame_set_string( cmp_frame, "/test/test3", "abcdefg" );
    g_assert_cmpint( kvp_frame_compare( cmp_frame, fixture->frame ), < , 0 );

    g_test_message( "Test when frames have equal number of slots second frame has different data in one slot" );
    g_assert_cmpint( kvp_frame_compare( fixture->frame, cmp_frame ), > , 0 );

    kvp_frame_delete( cmp_frame );
}
