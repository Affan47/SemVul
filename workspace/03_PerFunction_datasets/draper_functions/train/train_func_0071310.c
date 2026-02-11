request( const QHttpRequestHeader& header, QIODevice* data, QIODevice* to )
{
    QHttpRequestHeader h( header );
    applyProxy();
    applyUserAgent( h );

    m_buffer.clear();
    m_dataID = RedirectHttp::request( h, data, to );

    m_inProgress = true;

    return m_dataID;
}
