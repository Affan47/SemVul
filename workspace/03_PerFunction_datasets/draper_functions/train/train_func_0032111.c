unregisterFileDescriptor(zhttpd::api::socket_t fd)
{
    ZHTTPD_LOCK(this->_mutex);
    if (this->_fdlist.find(fd) != this->_fdlist.end())
    {
        this->_fdlist.erase(fd);

    }
    ZHTTPD_UNLOCK(this->_mutex);
}
