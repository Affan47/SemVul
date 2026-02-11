wasp_locate_file( wasp_string filename, wasp_list paths ){
    struct stat s;
    wasp_quad namelen = wasp_string_length( filename );

    while( paths ){
        wasp_string path = wasp_req_string( wasp_car( paths ) );
        wasp_quad pathlen = wasp_string_length( path );
        wasp_string n = wasp_make_string( namelen + pathlen + 1 );
        wasp_string_append_str( n, path );
#ifdef WASP_IN_WIN32
        wasp_string_append_byte( n, '\\' );
#else
        wasp_string_append_byte( n, '/' );
#endif
        wasp_string_append_str( n, filename );

        if(( stat( wasp_sf_string( n ), &s ) == 0 )&&( S_ISREG( s.st_mode ) ))return n;
        wasp_objfree( (wasp_object)n );

        paths = wasp_req_list( wasp_cdr( paths ) );
    }

    return NULL;
}
