currentTime() const
{
    if (!m_player)
        return 0;
    if (m_seeking)
        return m_currentTimeDuringSeek;
    return m_player->currentTime();
}
