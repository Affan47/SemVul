open(void* a)
{
    ACE_UNUSED_ARG(a);


    if (m_OutBuffer)
        { return -1; }


    m_OutActive = true;


    if (sWorldSocketMgr->OnSocketOpen(this) == -1)
        { return -1; }


    ACE_NEW_RETURN(m_OutBuffer, ACE_Message_Block(m_OutBufferSize), -1);


    ACE_INET_Addr remote_addr;

    if (peer().get_remote_addr(remote_addr) == -1)
    {
        sLog.outError("WorldSocket::open: peer ().get_remote_addr errno = %s", ACE_OS::strerror(errno));
        return -1;
    }

    m_Address = remote_addr.get_host_addr();


    WorldPacket packet(SMSG_AUTH_CHALLENGE, 4);
    packet << m_Seed;

    if (SendPacket(packet) == -1)
        { return -1; }


    if (reactor()->register_handler(this, ACE_Event_Handler::READ_MASK | ACE_Event_Handler::WRITE_MASK) == -1)
    {
        sLog.outError("WorldSocket::open: unable to register client handler errno = %s", ACE_OS::strerror(errno));
        return -1;
    }


    remove_reference();

    return 0;
}
