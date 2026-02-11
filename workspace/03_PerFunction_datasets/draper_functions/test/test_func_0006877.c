do_underline( const char * s,
              int          n )
{

    flps_output( "/len (%s) SW pop def\n", s );

    if ( n == -1 )
    {
        flps_output( "/ty CP exch pop %d sub def ", 1 + has_desc( s ) * 2 );
        flps_output( "/tx CP pop len sub def " );
        flps_output( "tx ty M len tx add ty LT S\n" );
    }
    else
    {
        char *t = fl_strdup( s );

        t[ n ] = '\0';
        flps_output( "/ul (%c) SW pop def\n", s[ n ] );
        flps_output( "/ty CP exch pop %d sub def ",
                     1 + is_desc( s [ n ] ) * 2 );
        flps_output( "/tx CP pop len sub (%s) SW pop add def\n", t );
        flps_output( "tx ty M ul tx add ty LT S\n" );
        fl_free( t );
    }
}
