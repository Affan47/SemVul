onTimeout(Socket& socket)
{
    log_debug("timeout; socket " << static_cast<void*>(&socket));

    _eventLoop.commitEvent(KeepAliveTimeoutEvent(&socket));
}
