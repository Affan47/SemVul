find( const char *s )
{
    PS_draw *p = psdraw,
            *ps = psdraw + sizeof psdraw / sizeof *psdraw;

    for ( ; p < ps; p++ )
        if ( strcmp( s, p->name ) == 0 )
        {
            define_symbol( p );
            return p;
        }

    return 0;
}
