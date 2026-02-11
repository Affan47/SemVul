setXml( const QByteArray &xml )
{
    m_xml = QString::fromUtf8( xml );
    prepareUrls();
}
