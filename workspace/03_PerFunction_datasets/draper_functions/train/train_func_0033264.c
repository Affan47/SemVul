ResourceManager_init() {
    if( rm ) {
        log_warn( "Tried to reinit the ResourceManager. Dont do this! :(\n" );
        return false;
    }

    rm = byte_alloc( sizeof( ResourceManager ) );
    check_mem( rm );

    u32Array_init( &rm->mHashes, 100 );
    u32Array_init( &rm->mHandles, 100 );

    return true;

error:
    ResourceManager_destroy();
    return false;
}
