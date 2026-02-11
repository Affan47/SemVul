receive (Message * msg,
                      bool      block)
{
    LOG4CPLUS_TRACE(logger, "[encmq::server::receive] ENTER (expected)");

    if (!node::receive(msg, block))
    {
        LOG4CPLUS_TRACE(logger, "[encmq::server::receive] EXIT = false");
        return false;
    }

    LOG4CPLUS_TRACE(logger, "[encmq::server::receive] EXIT = true");
    return true;
}
