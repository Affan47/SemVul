snprintf_buf_ts_s( const double s_)
{
        if ( s_ >= 60. )
                snprintf_buf_ts_m( s_/60);
        else
                snprintf_buf( "%.2gs", s_);
        return global::buf;
}
