toXml( QDomDocument& doc, QDomElement& elem ) const
{
    QDomElement c = doc.createElement( "constraint" );
    c.setAttribute( "type", "PreventDuplicates" );
    c.setAttribute( "field", QString::number( m_field ) );
    elem.appendChild( c );
}
