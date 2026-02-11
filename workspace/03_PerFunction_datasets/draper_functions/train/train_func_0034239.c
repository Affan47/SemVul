store( QDomNode & node, QDomDocument & document ) const
{

    storeBaseAnnotationProperties( node, document );


    QDomElement geomElement = document.createElement( "geom" );
    node.appendChild( geomElement );


    if ( geomType() != InscribedSquare )
        geomElement.setAttribute( "type", (int)geomType() );
    if ( geomInnerColor().isValid() )
        geomElement.setAttribute( "color", geomInnerColor().name() );
}
