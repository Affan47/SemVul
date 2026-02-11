threaded_traverse_worker( void *in ) {
    void **arg_list = (void **)in;
    set    *set   = arg_list[0];
    size_t *index = arg_list[1];
    size_t *count = arg_list[2];

    traverse_callback *cb = arg_list[3];
    void **cb_args = arg_list[4];

    while ( 1 ) {
        size_t idx = __sync_fetch_and_add( index, 1 );
        if ( idx >= *count ) return &rstat_ok;

        rstat check = cb( set, idx, cb_args );
        if ( check.bit.error ) {

            rstat *out = malloc( sizeof( rstat ));
            if ( out == NULL ) return &rstat_mem;
            *out = check;
            return out;
        }
    }
}
