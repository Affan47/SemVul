sendZip( const QString& inFile )
{
    QString username = The::settings().currentUser().username();
    QString passMd5 = The::settings().currentUser().password();

    if ( m_http )
        delete m_http;

    m_http = new CachedHttp( k_host, 80, this );
    connect( m_http, SIGNAL(requestFinished( int, bool )), SLOT(onUploadDone( int, bool )), Qt::QueuedConnection );
    connect( m_http, SIGNAL(dataSendProgress( int, int )), SLOT(onUploadProgress( int, int )) );


    time_t now;
    time( &now );
    QString time = QString::number( now );


    QString auth = passMd5 + time;
    QString authLower = passMd5.toLower() + time;

    QString authMd5 = UnicornUtils::md5Digest( auth.toUtf8() );
    QString authMd5Lower = UnicornUtils::md5Digest( authLower.toUtf8() );

    QString path = QString( "/bootstrap/index.php?user=%1&time=%2&auth=%3&authlower=%4" )
        .arg( username, time, authMd5, authMd5Lower );

    QFile* zipFile = new QFile( this );
    zipFile->setFileName( inFile );
    zipFile->open( QIODevice::ReadOnly );

    QHttpRequestHeader header( "POST", path, 1, 1 );
    header.setValue( "Host", k_host );
    header.setValue( "Content-type", "multipart/form-data, boundary=AaB03x" );
    header.setValue( "Cache-Control", "no-cache" );
    header.setValue( "Accept", "*/*" );

    QByteArray bytes;
    bytes.append( "--AaB03x\r\n" );
    bytes.append( "content-disposition: " );
    bytes.append( "form-data; name=\"agency\"\r\n" );
    bytes.append( "\r\n" );
    bytes.append( "0\r\n" );
    bytes.append( "--AaB03x\r\n" );
    bytes.append( "content-disposition: " );
    bytes.append( "form-data; name=\"bootstrap\"; filename=\"" + zipFile->fileName() + "\"\r\n" );
    bytes.append( "Content-Transfer-Encoding: binary\r\n" );
    bytes.append( "\r\n" );

    bytes.append( zipFile->readAll() );
    zipFile->close();

    bytes.append( "\r\n" );
    bytes.append( "--AaB03x--" );
    header.setContentLength( bytes.length() );

    qDebug() << "Sending " << path;

    emit percentageUploaded( 0 );

    m_reqId = m_http->request( header, bytes );
}
