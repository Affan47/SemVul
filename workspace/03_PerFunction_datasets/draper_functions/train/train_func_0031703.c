toXml( QDomDocument& xmldoc ) const
{
    QDomElement e = xmldoc.createElement( "generatorpreset" );
    e.setAttribute( "title", m_title );
    m_constraintTreeRoot->toXml( xmldoc, e );
    return new QDomElement( e );
}
