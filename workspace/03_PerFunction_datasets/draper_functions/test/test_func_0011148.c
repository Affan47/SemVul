do_underline( const char * s,
              int          n )
{
    ps_output( "/len (%s) SW pop def\n", s );

    if ( n == -1 )
    {
        ps_output( "/ty CP exch pop %d sub def ", 1 + has_desc( s ) * 2 );
        ps_output( "/tx CP pop len sub def " );
        ps_output( "tx ty M len tx add ty LT S\n" );
    }
    else
    {
        char *t = fl_strdup( s );
        *( t + n ) = '\0';
        ps_output( "/ul (%c) SW pop def\n", *( s + n ) );
        ps_output( "/ty CP exch pop %d sub def ", 1 + is_desc(s[ n ] ) * 2 );
        ps_output( "/tx CP pop len sub (%s) SW pop add def\n", t );
        ps_output( "tx ty M ul tx add ty LT S\n" );
        free( t );
    }
}
