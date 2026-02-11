turnOff()
{
    if(m_client.isConnected())
        m_client.close();
    m_connected = false;
    m_turnedOn = false;
    return true;
}
