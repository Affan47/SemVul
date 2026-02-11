main( int argc, const char** argv ){
    wasp_string wasp = wasp_find_arg0( argc, argv );
    wasp_init_waspvm( argc - 1, argv + 1 );

#ifndef WASP_IN_WIN32


    signal( SIGINT, wasp_handle_sigint );


    signal( SIGPIPE, SIG_IGN );
#endif

    wasp_load_linked( wasp );
    wasp_run_main( );

    if( wasp_show_globals ){
        wasp_list globals = wasp_get_globals( );
        while( globals ){
            wasp_show( wasp_car( wasp_pair_fv( wasp_car( globals ) ) ) );
            wasp_print( " -- " );
            wasp_show( wasp_value_type( wasp_cdr( wasp_pair_fv( wasp_car( globals ) ) ) )->name );
            wasp_newline( );
            globals = wasp_list_fv( wasp_cdr( globals ) );
        };
    };

    return 0;
}
