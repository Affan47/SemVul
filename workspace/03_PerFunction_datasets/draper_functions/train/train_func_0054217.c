us_testutil_start( int32_t US_UNUSED( sys_allocator_size ), int32_t session_allocator_size, int argc, const char **argv )
{
    bool r = true;
    (void)argc;
    (void)argv;
#if US_ENABLE_NETWORK
    r = us_platform_init_sockets();
    if ( !r )
    {
        return r;
    }
#endif


    us_testutil_sys_allocator = 0;
    us_testutil_session_allocator = 0;
#if US_ENABLE_MALLOC


    us_testutil_sys_allocator = us_malloc_allocator_init( &us_testutil_sys_allocator_impl );
#else
    (void)sys_allocator_size;


    us_testutil_sys_allocator = us_simple_allocator_init( &us_testutil_sys_allocator_impl,
                                                          &us_testutil_session_sys_buffer,
                                                          ( int32_t )( US_TESTUTIL_BUFFER_SIZE_IN_WORDS * sizeof( int32_t ) ) );
#endif
    (void)session_allocator_size;
    us_testutil_session_allocator
        = us_simple_allocator_init( &us_testutil_session_allocator_impl,
                                    &us_testutil_session_sys_buffer,
                                    ( int32_t )( US_TESTUTIL_BUFFER_SIZE_IN_WORDS * sizeof( int32_t ) ) );


    if ( !us_testutil_sys_allocator || !us_testutil_session_allocator )
    {
        r = false;
    }


#if US_ENABLE_PRINTING
#if US_ENABLE_STDIO


    us_testutil_printer_stdout = us_print_file_init( &us_testutil_printer_stdout_impl, stdout );
    us_testutil_printer_stderr = us_print_file_init( &us_testutil_printer_stderr_impl, stderr );
#else


    us_testutil_printer_stdout
        = us_printraw_init( &us_testutil_printer_stdout_impl, us_testutil_printbuffer_stdout, US_TESTUTIL_PRINTBUFFER_SIZE );
    us_testutil_printer_stderr
        = us_printraw_init( &us_testutil_printer_stderr_impl, us_testutil_printbuffer_stderr, US_TESTUTIL_PRINTBUFFER_SIZE );
#endif


    if ( !us_testutil_printer_stdout || !us_testutil_printer_stderr )
    {
        r = false;
    }
    us_stdout = us_testutil_printer_stdout;
    us_stderr = us_testutil_printer_stderr;
#endif
    return r;
}
