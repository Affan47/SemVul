find_type_name( int cln,
                int tyn )
{
    int i;
    static char buf[ MAX_TYPE_NAME_LEN ];

    for ( i = 0; i < cnumb; i++ )
        if ( classes[ i ].cn == cln )
            return classes[ i ].types[ tyn ].tname;
    sprintf( buf, "%d", tyn );
    return buf;
}
