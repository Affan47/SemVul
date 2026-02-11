registerResource( int type,
                              const char *symbol,
                              const char *fn,
                              unsigned int filesize )
{
    struct Resource *it = 0;
    struct Resource *res = (struct Resource *)malloc( sizeof( struct Resource ) );
    res->type = type;
    res->symbol = strdup( symbol );
    res->symbolSize = strlen( res->symbol ) + 1;
    res->filename = strdup( fn );
    res->size = filesize;
    if ( type == TEXT )
        ++res->size;
    res->next = 0;

    if ( !resources ) {
        resources = res;
    } else {
        for ( it = resources; it->next != 0; it = it->next )
            ;
        it->next = res;
    }

    if ( verbosity > 0 )
        printf( "Registered resurce %s (type %d) => %s (%d bytes)\n",
                symbol, type, fn, filesize );
}
