addApplet( const QString& name, const QStringList& args )
{
    QVariantList argList;
    QStringListIterator i(args);
    while( i.hasNext() )
        argList << QVariant( i.next() );

    if( !containment() )
        contextScene()->addContainment( "amarok_containment_vertical" );

    return containment()->addApplet( name, argList );
}
