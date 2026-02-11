parseListBegin(char next)
{
    m_bridge.mapListItem(hexDecode(m_name));
    m_socket.putback(next);
    m_state.pop();
    m_name.erase();
}
