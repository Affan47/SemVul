start()
{
    time_t now;
    time( &now );
    QString time = QString::number( now );


    QString auth = passwordMd5() + time;
    QString authLower = passwordMd5Lower() + time;

    QString authMd5 = UnicornUtils::md5Digest( auth.toUtf8() );
    QString authMd5Lower = UnicornUtils::md5Digest( authLower.toUtf8() );

    QString baseUrl = "http://www.last.fm/fingerprint/query/";
    QString url = baseUrl +
        "?artist=" + QUrl::toPercentEncoding( m_track.artist() ) +
        "&album=" + QUrl::toPercentEncoding( m_track.album() ) +
        "&track=" + QUrl::toPercentEncoding( m_track.track() ) +
        "&duration=" + QString::number( m_track.duration() ) +
        "&mbid=" + QUrl::toPercentEncoding( m_track.mbId() ) +
        "&filename=" + QUrl::toPercentEncoding( QFileInfo( m_track.path() ).completeBaseName() ) +
        "&tracknum=" + QString::number( m_track.trackNr() ) +
        "&username=" + username() +
        "&sha256=" + sha256() +
        "&time=" + time +
        "&auth=" + authMd5 +
        "&authlower=" + authMd5Lower +
        "&fpversion=" + QUrl::toPercentEncoding( fpVersion() ) +
        "&fulldump=false" +
        "&clientversion=" + clientVersion();

    #ifndef QT_NO_DEBUG


    #endif


    qDebug() << url;

    QHttpRequestHeader header( "POST", url, 1, 1 );
    setHost( "www.last.fm", 80 );
    header.setValue( "Host", "www.last.fm" );
    header.setValue( "Content-Type", "multipart/form-data; boundary=----------------------------8e61d618ca16" );
    header.setValue( "Accept", "*/*" );

    QByteArray bytes;
    bytes.append( "------------------------------8e61d618ca16\r\n" );
    bytes.append( "Content-Disposition: " );
    bytes.append( "form-data; name=\"fpdata\"" );
    bytes.append( "\r\n\r\n" );

    bytes.append( data() );

    bytes.append( "\r\n");
    bytes.append( "------------------------------8e61d618ca16--\r\n");

    int contentLength = bytes.length();
    header.setContentLength(contentLength);

    post( header, bytes );
}
