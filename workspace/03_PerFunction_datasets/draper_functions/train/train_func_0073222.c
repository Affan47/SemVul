fli_xdashedlinestyle( Display    * d,
                      GC           gc,
                      const char * dash,
                      int          ndash )
{
    static char default_dash[ ] = { 4, 4 };

    if ( dash == NULL )
    {
        dash = default_dash;
        ndash = 2;
    }

    XSetDashes( d, gc, 0, ( char * ) dash, ndash );
}
