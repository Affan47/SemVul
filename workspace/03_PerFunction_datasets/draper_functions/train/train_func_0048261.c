handle_close(ACE_HANDLE h, ACE_Reactor_Mask)
{
    if (closing_)
        return -1;
    DEBUG_LOG("RASocket::handle_close");
    ACE_GUARD_RETURN(ACE_Thread_Mutex, Guard, outBufferLock, -1);

    closing_ = true;

    if (h == ACE_INVALID_HANDLE)
        peer().close_writer();
    remove_reference();
    return 0;
}
