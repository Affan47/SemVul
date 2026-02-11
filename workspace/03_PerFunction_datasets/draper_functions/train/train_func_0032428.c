checkConnect()
{
    log_trace("checkConnect");

    int sockerr;
    socklen_t optlen = sizeof(sockerr);


    if( ::getsockopt(this->fd(), SOL_SOCKET, SO_ERROR, &sockerr, &optlen) != 0 )
    {

        int e = errno;
        close();
        throw SystemError(e, "getsockopt");
    }

    if (sockerr == 0)
    {
        log_debug("connected successfully to " << getPeerAddr());
        _isConnected = true;
    }

    return sockerr;
}
