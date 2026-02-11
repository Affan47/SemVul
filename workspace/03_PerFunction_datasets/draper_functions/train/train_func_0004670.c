ff_get_fd_file( const char  * str,
                int           merge )
{
    ff_close( );

    ff.merge = merge;

    fl_use_fselector( LOAD_FSELECTOR );


    if ( ! str || ! *str )
    {
        str = fl_show_fselector( merge ? "Filename to merge forms from" :
                                 "Filename to load forms from",
                                 "", "*.fd", "" );

        if ( ! str || ! *str )
            return -1;
    }


    ff.fname = append_fd_suffix( str );


    if ( ! ( ff.fp = fopen( ff.fname, "r" ) ) )
    {
        if ( ! fdopt.conv_only )
            fl_show_alert( "Can't open file for reading", ff.fname, "", 0 );
        else
            M_err( "ff_get_fd_file", "Can't open '%s' for reading", ff.fname );
        ff_close( );
        return -1;
    }

    if ( ff_get_line( ) < 0 )
    {
        if ( ! fdopt.conv_only )
            fl_show_alert( "Nothing to be read from", ff.fname, "", 0 );
        else
            M_err( "ff_get_fd_file", "Nothing to be read from '%s'",
                   ff.fname );
        ff_close( );
        return -1;
    }

    return 0;
}
