createNewStartupId()
    {


    struct timeval tm;
    gettimeofday( &tm, NULL );
    char hostname[ 256 ];
    hostname[ 0 ] = '\0';
    if (!gethostname( hostname, 255 ))
	hostname[sizeof(hostname)-1] = '\0';
#ifdef Q_WS_X11
    unsigned long qt_x_user_time = QX11Info::appUserTime();
#else
    unsigned long qt_x_user_time = 0;
#endif
    QByteArray id = QString::fromLatin1( "%1;%2;%3;%4_TIME%5" ).arg( hostname ).arg( tm.tv_sec )
        .arg( tm.tv_usec ).arg( getpid()).arg( qt_x_user_time ).toUtf8();
    kDebug( 172 ) << "creating: " << id << ":" << (qApp ? qAppName() : QString("unnamed app") );
    return id;
    }
