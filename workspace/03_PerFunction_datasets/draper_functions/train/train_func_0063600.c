likelyLastTrack()
{
    doItemListsMaintenance();

    return m_historyItems.isEmpty() ? 0 : m_historyItems.last();
}
