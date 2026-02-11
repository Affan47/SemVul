DownloadInfo()
{
    #ifdef WIN32
        QString platform = "win";
    #elif defined Q_WS_X11
        QString platform = "linux";
    #else
        QString platform = "mac";
    #endif

    QString version = The::settings().version();
    QString user = The::settings().currentUsername();
    QString host = Request::baseHost();
    LastFmApplication* app = qobject_cast<LastFmApplication*>( QApplication::instance() );

    Q_ASSERT( !version.isEmpty() && !user.isEmpty()  && !host.isEmpty() );

    QString path = QString( "/ass/upgrade.xml.php?platform=%1&version=%2&lang=%3&user=%4" )
        .arg( platform )
        .arg( version )
        .arg( app->languageCode() )
        .arg( QString( QUrl::toPercentEncoding( user ) ) );


    mHttp = new CachedHttp( host, 80, this );
    mGetId = mHttp->get( path );

    connect(mHttp, SIGNAL(requestFinished(int, bool)),
            this,  SLOT(downloadFinished(int, bool)));

    connect(mHttp, SIGNAL(dataReadProgress(int, int)),
            this,  SIGNAL(progressMade(int, int)));

    connect(mHttp, SIGNAL(stateChanged(int)),
            this,  SLOT(statusChanged(int)));

    connect(mHttp, SIGNAL(dataSendProgress(int, int)),
            this,  SLOT(sendProgress(int, int) ));

    connect(mHttp, SIGNAL(readyRead(const QHttpResponseHeader&)),
            this,  SLOT(readyRead(const QHttpResponseHeader&) ));

    connect(mHttp, SIGNAL(requestStarted(int)),
            this,  SLOT(requestStarted(int)));

    connect(mHttp, SIGNAL(responseHeaderReceived ( const QHttpResponseHeader & )),
            this,  SLOT(responseHeaderReceived ( const QHttpResponseHeader & )));

    LOGL(3, "Requesting update info from: " << host << path );
}
