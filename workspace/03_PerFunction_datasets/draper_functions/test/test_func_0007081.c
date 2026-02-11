panic( void )
    {
    Map** mm;
    Map* m;

    syslog( LOG_ERR, "mmc panic - freeing all unreferenced maps" );


    for ( mm = &maps; *mm != (Map*) 0; )
    {
    m = *mm;
    if ( m->refcount == 0 )
        really_unmap( mm );
    else
        mm = &(*mm)->next;
    }
    }
