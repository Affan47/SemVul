interpretPercentSpacing( QString value, int base, bool *ok )
{
    if ( !value.endsWith( "%" ) )
    {
        if ( ok != 0 )
            *ok = false;
        return 0;
    }

    value.truncate( value.length() - 1 );
    bool float_ok;
    float factor = value.toFloat( &float_ok );
    if ( float_ok && factor >= 0 )
    {
        if ( ok != 0 )
            *ok = true;
        return ( int )( base * factor / 100.0 );
    }

    qWarning( "interpretPercentSpacing(): could not parse \"%s%%\"", value.toLatin1().data() );
    if ( ok != 0 )
        *ok = false;
    return 0;
}
