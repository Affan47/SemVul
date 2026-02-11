OnSocketOpen(WorldSocket* sock)
{

    if (m_SockOutKBuff >= 0)
    {
        if (sock->peer().set_option(SOL_SOCKET, SO_SNDBUF, (void*)&m_SockOutKBuff, sizeof(int)) == -1 && errno != ENOTSUP)
        {
            sLog.outError("WorldSocketMgr::OnSocketOpen set_option SO_SNDBUF");
            return -1;
        }
    }

    static const int ndoption = 1;


    if (m_UseNoDelay)
    {
        if (sock->peer().set_option(ACE_IPPROTO_TCP, TCP_NODELAY, (void*)&ndoption, sizeof(int)) == -1)
        {
            sLog.outError("WorldSocketMgr::OnSocketOpen: peer().set_option TCP_NODELAY errno = %s", ACE_OS::strerror(errno));
            return -1;
        }
    }

    sock->m_OutBufferSize = static_cast<size_t>(m_SockOutUBuff);


    size_t min = 1;

    MANGOS_ASSERT(m_NetThreadsCount >= 1);

    for (size_t i = 1; i < m_NetThreadsCount; ++i)
        if (m_NetThreads[i].Connections() < m_NetThreads[min].Connections())
            { min = i; }

    return m_NetThreads[min].AddSocket(sock);
}
