toXml( QXmlStreamWriter *writer ) const
{
    foreach( Dynamic::BiasPtr bias, m_biases )
    {
        writer->writeStartElement( bias->name() );
        bias->toXml( writer );
        writer->writeEndElement();
    }
}
