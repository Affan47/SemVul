showHome()
{
    DEBUG_BLOCK

    m_curState = Home;
    loadConfig();
    messageNotify( m_curState );
}
