ANET_Error()
{
    int error = 0;
    nSocketError aError = nSocketError_Ignore;


    static char const * section = "NETERROR";
    if ( !tRecorder::PlaybackStrict( section, aError ) )
    {

#ifdef WIN32
        error = WSAGetLastError();
#else
        error = errno;
#endif
        switch ( error )
        {
        case EADDRINUSE:
            break;
        case ENOTSOCK:
            aError = nSocketError_Reset;
            break;
        case ECONNRESET:
            aError = nSocketError_Reset;
            break;
        case ECONNREFUSED:
            break;
        case EWOULDBLOCK:
        case ENETUNREACH:
            aError = nSocketError_Ignore;
            break;


        case ENETDOWN:
            break;
        case EFAULT:
            aError = nSocketError_Reset;
            break;
        case EINTR:
            break;
        case EINVAL:
            break;
        case EISCONN:
            break;
        case ENETRESET:
            break;
        case EOPNOTSUPP:
        case EAFNOSUPPORT:
        case EADDRNOTAVAIL:
            aError = nSocketError_Reset;
            break;
        case ESHUTDOWN:
            break;
    #ifndef WIN32
        case EMSGSIZE:
            break;
    #endif
        case ETIMEDOUT:
            break;
        default:
    #ifdef DEBUG
            con << "Unknown network error " << error << "\n";
    #endif
            break;
        }
    }


    tRecorder::Record( section, aError );


    return aError;
}
