us_logger_init_stdio_files( const char *outfilename, const char *errfilename )
{
    bool r = false;
    us_logger_stdio_out = fopen( outfilename, "at" );
    if ( us_logger_stdio_out )
    {
        us_logger_stdio_err = fopen( errfilename, "at" );
        if ( us_logger_stdio_err )
        {
            us_logger_stdio_files = true;
            us_log_error_proc = us_log_error_stdio;
            us_log_warn_proc = us_log_warn_stdio;
            us_log_info_proc = us_log_info_stdio;
            us_log_debug_proc = us_log_debug_stdio;
            us_logger_finish = us_logger_stdio_finish;
        }
        else
        {
            fclose( us_logger_stdio_out );
        }
    }
    return r;
}
