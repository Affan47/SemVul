getStatus() const
{
    if (this->_status != PROCESS_STATUS::FINISHED)
    {
        int status;
        while (::waitpid(this->_pid, &status, WNOHANG) < 0 && errno == EINTR)
            ;
        if (WIFEXITED(status))
            this->_status = PROCESS_STATUS::FINISHED;
    }
    return (this->_status);
}
