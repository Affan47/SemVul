store( QDomNode & node, QDomDocument & document ) const
{

    storeBaseAnnotationProperties( node, document );


    QDomElement inkElement = document.createElement( "ink" );
    node.appendChild( inkElement );


    const QList< QLinkedList<QPointF> > paths = inkPaths();
    if ( paths.count() < 1 )
        return;
    QList< QLinkedList<QPointF> >::const_iterator pIt = paths.begin(), pEnd = paths.end();
    for ( ; pIt != pEnd; ++pIt )
    {
        QDomElement pathElement = document.createElement( "path" );
        inkElement.appendChild( pathElement );
        const QLinkedList<QPointF> & path = *pIt;
        QLinkedList<QPointF>::const_iterator iIt = path.begin(), iEnd = path.end();
        for ( ; iIt != iEnd; ++iIt )
        {
            const QPointF & point = *iIt;
            QDomElement pointElement = document.createElement( "point" );
            pathElement.appendChild( pointElement );
            pointElement.setAttribute( "x", QString::number( point.x() ) );
            pointElement.setAttribute( "y", QString::number( point.y() ) );
        }
    }
}
