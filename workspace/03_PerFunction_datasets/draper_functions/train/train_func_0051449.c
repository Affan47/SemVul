wasp_load_linked( wasp_string prog_path ){
    wasp_pair linked = wasp_thaw_tail( wasp_sf_string( prog_path ) );
    wasp_root_value( linked );

    if( ! linked ){
        if( wasp_argv ){
            wasp_string src_path = wasp_string_fv( wasp_car( wasp_argv ) );
            wasp_file src_file = wasp_open_file( wasp_sf_string( src_path ),
                                               "r", 0600 );
            wasp_run( wasp_thaw_str( wasp_read_file( src_file, 1 << 30 ) ), NULL );
        }
    }else while( linked ){
        wasp_value next = wasp_car( linked );
        if( next ) wasp_run( next, NULL );
        linked = wasp_list_fv( wasp_cdr( linked ) );
    }
}
