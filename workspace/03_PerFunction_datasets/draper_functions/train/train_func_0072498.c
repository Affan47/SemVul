writeOutline( const OpmlOutline *outline )
{
    bool hasChildren = outline->children().count() != 0;
    if( hasChildren && ( outline->opmlNodeType() != IncludeNode ) )
        _x->writeStartElement( "outline" );
    else
        _x->writeEmptyElement( "outline" );
    QMapIterator<QString, QString> ai( outline->attributes() );
    while( ai.hasNext() )
    {
        ai.next();
        _x->writeAttribute( ai.key(), ai.value() );
    }


    if( hasChildren && ( outline->opmlNodeType() != IncludeNode ) )
    {
        foreach( const OpmlOutline *childOutline, outline->children() )
            writeOutline( childOutline );
        _x->writeEndElement();
    }
}
