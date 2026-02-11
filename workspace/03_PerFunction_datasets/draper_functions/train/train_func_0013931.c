handle_output(ACE_HANDLE)
{
    ACE_GUARD_RETURN(ACE_Thread_Mutex, Guard, outBufferLock, -1);

    if (closing_)
        { return -1; }

    if (!outputBufferLen)
    {
        if (reactor()->cancel_wakeup(this, ACE_Event_Handler::WRITE_MASK) == -1)
        {
            sLog.outError("RASocket::handle_output: error while cancel_wakeup");
            return -1;
        }
        outActive = false;
        return 0;
    }
#ifdef MSG_NOSIGNAL
    ssize_t n = peer().send(outputBuffer, outputBufferLen, MSG_NOSIGNAL);
#else
    ssize_t n = peer().send(outputBuffer, outputBufferLen);
#endif

    if (n <= 0)
        { return -1; }

    ACE_OS::memmove(outputBuffer, outputBuffer + n, outputBufferLen - n);

    outputBufferLen -= n;

    return 0;
}
