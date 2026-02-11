file_get_order_list( const char *orderfile )
{
    List *l = 0;
    FILE *f = fopen( orderfile, "r" );
    if (!f) {
        fprintf( stderr, tr("%s cannot be opened\n"), orderfile );
        return 0;
    }

    l = file_read_lines( f );
    fclose( f );

    return l;
}
