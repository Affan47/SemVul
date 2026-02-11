RemoveQueuedSession(WorldSession* sess)
{

    uint32 sessions = GetActiveSessionCount();

    uint32 position = 1;
    Queue::iterator iter = m_QueuedSessions.begin();


    bool found = false;

    for (; iter != m_QueuedSessions.end(); ++iter, ++position)
    {
        if (*iter == sess)
        {
            sess->SetInQueue(false);
            iter = m_QueuedSessions.erase(iter);
            found = true;
            break;
        }
    }


    if (!found && sessions)
        --sessions;


    if ((!m_playerLimit || (int32)sessions < m_playerLimit) && !m_QueuedSessions.empty())
    {
        WorldSession* pop_sess = m_QueuedSessions.front();
        pop_sess->SetInQueue(false);
        pop_sess->SendAuthWaitQue(0);
        pop_sess->SendAddonsInfo();

        WorldPacket pkt(SMSG_CLIENTCACHE_VERSION, 4);
        pkt << uint32(getConfig(CONFIG_UINT32_CLIENTCACHE_VERSION));
        pop_sess->SendPacket(&pkt);

        pop_sess->SendAccountDataTimes(GLOBAL_CACHE_MASK);
        pop_sess->SendTutorialsData();

        m_QueuedSessions.pop_front();


        iter = m_QueuedSessions.begin();
        position = 1;
    }


    for (; iter != m_QueuedSessions.end(); ++iter, ++position)
        (*iter)->SendAuthWaitQue(position);

    return found;
}
