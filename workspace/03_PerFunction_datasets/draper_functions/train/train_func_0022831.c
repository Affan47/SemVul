start()
{
    QString lang_code = language();
    if (lang_code.isEmpty())
        lang_code = "en";

    QString urlWithoutProtocol = m_stationUrl;
    if ( m_stationUrl.startsWith( "lastfm://" ) )
    {
        urlWithoutProtocol = m_stationUrl.right( m_stationUrl.size() - 9 );
    }

    QString url = urlWithoutProtocol.contains( "%" )
        ? urlWithoutProtocol
        : QString( QUrl::toPercentEncoding( urlWithoutProtocol, "/," ) );

    QString path;
    if ( m_stationUrl.isPlaylist() )
    {

        path = "/1.0/webclient/getresourceplaylist.php?sk=" + m_session +
               "&url=lastfm://" + url +
               "&desktop=1" +
               "&api_key=9d1bbaef3b443eb97973d44181d04e4b";

        m_hasXspf = true;
    }
    else
    {

        path = m_basePath +
               "/adjust.php?session=" + m_session +
               "&url=lastfm://" + url +
               "&lang=" + lang_code +
               "&api_key=9d1bbaef3b443eb97973d44181d04e4b";
    }

    get( path );
}
