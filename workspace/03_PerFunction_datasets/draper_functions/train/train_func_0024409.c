columnspacing() const
{
    QString value = explicitAttribute( "columnspacing" );
    if ( value.isNull() )
        return ( int )( 0.8 * em() );
    bool ok;
    int r = interpretSpacing( value, &ok );

    if ( ok )
        return r;
    else
        return ( int )( 0.8 * em() );
}
