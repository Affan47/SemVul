us_test_buffer( void )
{
    bool r = true;
    int repeat_count = 10;
    int big_loop = 100;
    us_buffer_t *buf = us_buffer_create( us_testutil_sys_allocator, 500 );
    if ( buf )
    {
        int i;
        int j;
        for ( j = 0; j < big_loop; ++j )
        {
            for ( i = 0; i < repeat_count; ++i )
            {
                bool r1 = false;
                if ( us_buffer_append_rounded_string( buf, "Rounded String" ) )
                {
                    if ( us_buffer_append_int32( buf, 0x12345678 ) )
                    {
                        if ( us_buffer_append_uint64( buf, 0x89abcdef, 0x01234567 ) )
                        {
                            r1 = true;
                        }
                    }
                }
                if ( !r1 )
                {
                    us_log_error( "unable to append items" );
                }
                r &= r1;
                if ( !r )
                    break;
            }
            for ( i = 0; i < repeat_count; ++i )
            {
                bool r1 = false;
                {
                    char rs[128];
                    if ( us_buffer_read_rounded_string( buf, rs, sizeof( rs ) ) )
                    {
                        if ( strcmp( rs, "Rounded String" ) == 0 )
                        {
                            int32_t v;
                            if ( us_buffer_read_int32( buf, &v ) )
                            {
                                if ( v == 0x12345678 )
                                {
                                    uint32_t a, b;
                                    if ( us_buffer_read_uint64( buf, &a, &b ) )
                                    {
                                        if ( a == 0x89abcdef && b == 0x01234567 )
                                        {
                                            r1 = true;
                                        }
                                        else
                                        {
                                            us_log_error( "unable to validate uint64" );
                                        }
                                    }
                                    else
                                    {
                                        us_log_error( "unable to read uint64" );
                                    }
                                }
                                else
                                {
                                    us_log_error( "unable to validate int32" );
                                }
                            }
                            else
                            {
                                us_log_error( "unable to read int32" );
                            }
                        }
                        else
                        {
                            us_log_error( "unable to validate rounded string" );
                        }
                    }
                    else
                    {
                        us_log_error( "unable to read rounded string" );
                    }
                }
                r &= r1;
                if ( !r )
                {
#if US_ENABLE_PRINTING
                    us_testutil_printer_stdout->printf( us_testutil_printer_stdout, "contents of test buffer:\n" );
                    us_buffer_print( buf, us_testutil_printer_stdout );
                    us_testutil_printer_stdout->printf( us_testutil_printer_stdout, "\n" );
#endif
                    break;
                }
            }
        }
    }
    else
    {
        us_log_error( "expected to allocate 1024 bytes from allocator for buffer but failed" );
    }
    r &= us_test_buffer_queue();
    return r;
}
