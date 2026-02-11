toXml( QXmlStreamWriter *writer ) const
{
    writer->writeTextElement( "title", m_title );
    writer->writeStartElement( m_bias->name() );
    m_bias->toXml( writer );
    writer->writeEndElement();
}
