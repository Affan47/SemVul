PL_strnprbrk(const char *s, const char *list, PRUint32 max)
{
    const char *p;
    const char *r;

    if( ((const char *)0 == s) || ((const char *)0 == list) ) return (char *)0;

    for( r = s; max && *r; r++, max-- )
        ;

    for( r--; r >= s; r-- )
        for( p = list; *p; p++ )
            if( *r == *p )
                return (char *)r;

    return (char *)0;
}
