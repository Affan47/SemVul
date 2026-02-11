notifyReady(Sea::Player player)
{
    if (player != m_player) {
        m_protocol->send(MessagePtr(new BeginMessage()));
    }
}
