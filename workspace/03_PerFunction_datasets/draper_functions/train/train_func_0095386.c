depth() const
{
    QRect cr;
    if ( firstChild() == 0 )
        cr = QRect( 0, 0, 0, 0 );
    else
        cr = firstChild()->myRect();

    QString value = explicitAttribute( "depth" );
    if ( value.isNull() )
        return cr.bottom();

    bool ok;
    int h = interpretSpacing( value, cr.bottom(), &ok );
    if ( ok )
        return h;

    return cr.bottom();
}
