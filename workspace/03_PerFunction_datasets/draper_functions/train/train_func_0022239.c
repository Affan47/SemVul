join()
{
    if (!this->_running)
        return;
    ::pthread_join(*this->_thread, 0);
    this->_running = false;
}
