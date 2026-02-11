ff_read_alignment( FL_OBJECT * obj )
{
    int r;

    if ( ( r = ff_read( "%a", &obj->align ) ) < 0 )
        return ff_err( "Can't read expected object alignment" );

    if ( r == 0 )
        return ff_err( "\"alignment\" key without or invalid value" );

    if ( fd_magic == MAGIC2 )
        obj->align = new_align( obj->align );

    return 0;
}
