delete_tmp_files(void)
{
    if( g_file_test( gms_get_in_filename(gms_hnd),G_FILE_TEST_EXISTS) == TRUE )
        g_unlink( gms_get_in_filename(gms_hnd) ) ;
    if( g_file_test( gms_get_out_filename(gms_hnd),G_FILE_TEST_EXISTS) == TRUE )
        g_unlink( gms_get_out_filename(gms_hnd) ) ;
    if( g_file_test( gms_get_filter_filename(gms_hnd),G_FILE_TEST_EXISTS) == TRUE )
        g_unlink( gms_get_filter_filename(gms_hnd) ) ;
}
