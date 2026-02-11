us_test_http( void )
{
    bool r = true;
    if ( !us_test_http_request() )
    {
        r = false;
        us_log_error( "http request test failed" );
    }
    if ( !us_test_http_response() )
    {
        r = false;
        us_log_error( "http response test failed" );
    }
    return r;
}
