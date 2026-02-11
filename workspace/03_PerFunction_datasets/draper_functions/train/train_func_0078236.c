KickAll()
{
    m_QueuedSessions.clear();


    for (SessionMap::const_iterator itr = m_sessions.begin(); itr != m_sessions.end(); ++itr)
        itr->second->KickPlayer();
}
