toXml( QXmlStreamWriter *writer ) const
{
    Q_UNUSED( writer );
    writer->writeComment("Replacement");
    writer->device()->write( m_html.left( m_html.size() - m_name.length() - 3 ) );
}
