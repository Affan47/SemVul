onFailurePrivate( int error_code, const QString &error_string )
{
    m_timeout_timer.stop();

    QDebugBlock block( QString(__PRETTY_FUNCTION__) + " - " + objectName() );

    LOG( 1, objectName() << "\n" <<
        "  Http response: " << m_http->lastResponse().statusCode() << "\n" <<
        "  QHttp error code: " << error_code << "\n" <<
        "  QHttp error text: " << error_string << "\n" <<
        "  Request: " << m_http->host() + m_http->currentRequest().path() << "\n" <<
        "  Bytes returned: " << m_http->bytesAvailable() << "\n"
        );

    qDebug() << error_code << error_string;

    switch (error_code)
    {
        case QHttp::NoError:
            Q_ASSERT( !"can't happen" );
            break;

        case QHttp::Aborted:
            m_result = Request_Aborted;
            break;

        case QHttp::HostNotFound:
            m_result = Request_HostNotFound;
            break;

        #if QT_VERSION >= 0x040300
        case QHttp::ProxyAuthenticationRequiredError:
            m_result = Request_ProxyAuthenticationRequired;
            break;
        #endif

        case QHttp::ConnectionRefused:
        case QHttp::UnexpectedClose:
        case QHttp::InvalidResponseHeader:
        case QHttp::UnknownError:
        case QHttp::WrongContentLength:
            tryAgain();
            return;
    }

    emit result( this );
}
