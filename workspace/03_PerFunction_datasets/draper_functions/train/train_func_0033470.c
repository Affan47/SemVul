qMsgHandler( QtMsgType type, const char* msg )
{
#ifndef NDEBUG
#ifdef WIN32
    qWinMsgHandler( type, msg );
#else
	Q_UNUSED( type );
    fprintf( stderr, "%s\n", msg );
    fflush( stderr );
#endif
#endif

    Logger* theLog = Logger::the();
    if (!theLog) return;

    static int spam = 0;
    static QByteArray previous_msg;

    if (previous_msg == msg) {
        ++spam;
        return;
    }

    if (spam) {

        theLog->log( QString( "Times above line spammed: %L1").arg( spam + 1 ).toUtf8() );
        spam = 0;
    }

    previous_msg = msg;
    theLog->log( msg );
}
