flps_linestyle( int n )
{
    if ( ps_ls == n )
        return;

    switch ( n )
    {
        case FL_DOT :
            flps_output( "DT " );
            break;

        case FL_DOTDASH :
            flps_output( "DTD " );
            break;

        case FL_DASH :
            flps_output( "D " );
            break;

        case FL_LONGDASH :
            flps_output( "LD " );
            break;

        case FL_SOLID :
        case FL_USERDASH :
        case FL_USERDOUBLEDASH :
        case -1:
            flps_output( "SL " );
            ps_ls = FL_SOLID;
            break;

        default:
            fprintf( stderr, "Unknown dashstyle: %d\n", n );
            return;
    }

    ps_ls = n;
}
