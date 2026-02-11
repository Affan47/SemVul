poll(short events) const
{
    struct pollfd fds;
    fds.fd = _impl->fd();
    fds.events = events;

    log_debug("poll timeout " << getTimeout());

    int p = ::poll(&fds, 1, getTimeout());

    log_debug("poll returns " << p << " revents " << fds.revents);

    if (p < 0)
    {
      log_error("error in poll; errno=" << errno);
      throw SystemError("poll");
    }
    else if (p == 0)
    {
      log_debug("poll timeout (" << getTimeout() << ')');
      throw IOTimeout();
    }

    return fds.revents;
}
