file_archscan(
    const char * archive,
    scanback func,
    void * closure )
{
# ifndef NO_AR
    struct ar_hdr ar_hdr;
    char buf[ MAXJPATH ];
    long offset;
    char    *string_table = 0;
    int fd;

    if ( ( fd = open( archive, O_RDONLY, 0 ) ) < 0 )
        return;

    if ( read( fd, buf, SARMAG ) != SARMAG ||
        strncmp( ARMAG, buf, SARMAG ) )
    {
        close( fd );
        return;
    }

    offset = SARMAG;

    if ( DEBUG_BINDSCAN )
        printf( "scan archive %s\n", archive );

    while ( ( read( fd, &ar_hdr, SARHDR ) == SARHDR )
           && !( memcmp( ar_hdr.ar_fmag, ARFMAG, SARFMAG )
#ifdef ARFZMAG

              && memcmp( ar_hdr.ar_fmag, ARFZMAG, SARFMAG )
#endif
          ) )
    {
        char   lar_name_[257];
        char * lar_name = lar_name_ + 1;
        long   lar_date;
        long   lar_size;
        long   lar_offset;
        char * c;
        char * src;
        char * dest;
        OBJECT * member;

        strncpy( lar_name, ar_hdr.ar_name, sizeof(ar_hdr.ar_name) );

        sscanf( ar_hdr.ar_date, "%ld", &lar_date );
        sscanf( ar_hdr.ar_size, "%ld", &lar_size );

        if (ar_hdr.ar_name[0] == '/')
        {
        if (ar_hdr.ar_name[1] == '/')
        {


            string_table = (char *)BJAM_MALLOC_ATOMIC(lar_size);
            lseek(fd, offset + SARHDR, 0);
            if (read(fd, string_table, lar_size) != lar_size)
            printf("error reading string table\n");
        }
        else if (string_table && ar_hdr.ar_name[1] != ' ')
        {


            dest = lar_name;
            lar_offset = atoi(lar_name + 1);
            src = &string_table[lar_offset];
            while (*src != '/')
            *dest++ = *src++;
            *dest = '/';
        }
        }

        c = lar_name - 1;
        while ( ( *++c != ' ' ) && ( *c != '/' ) ) ;
        *c = '\0';

        if ( DEBUG_BINDSCAN )
        printf( "archive name %s found\n", lar_name );

        sprintf( buf, "%s(%s)", archive, lar_name );

        member = object_new( buf );
        (*func)( closure, member, 1 , (time_t)lar_date );
        object_free( member );

        offset += SARHDR + ( ( lar_size + 1 ) & ~1 );
        lseek( fd, offset, 0 );
    }

    if ( string_table )
        BJAM_FREE( string_table );

    close( fd );

# endif

}
