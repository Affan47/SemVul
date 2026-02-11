writeFiles( int fd )
{
    int i;
    int npad;
    struct Resource *it = resources;

    for ( it = resources; it != 0; it = it->next ) {
        if ( copyFileToFD( it->filename, fd ) == -1 ) {
            it->ignore = TRUE;
        } else {
            it->ignore = FALSE;


            if ( it->type == TEXT )
                write( fd, "\0", 1 );

            if ( it->next ) {

                npad = padding( it->size );
                for ( i = 0; i < npad; ++i )
                    write( fd, "\0", 1 );
            }
        }
    }

    return 0;
}
