handle_input_header(void)
{
    MANGOS_ASSERT(m_RecvWPct == NULL);

    MANGOS_ASSERT(m_Header.length() == sizeof(ClientPktHeader));

    m_Crypt.DecryptRecv((uint8*) m_Header.rd_ptr(), sizeof(ClientPktHeader));

    ClientPktHeader& header = *((ClientPktHeader*) m_Header.rd_ptr());

    EndianConvertReverse(header.size);
    EndianConvert(header.cmd);

    if ((header.size < 4) || (header.size > 10240) || (header.cmd  > 10240))
    {
        sLog.outError("WorldSocket::handle_input_header: client sent malformed packet size = %d , cmd = %d",
                      header.size, header.cmd);

        errno = EINVAL;
        return -1;
    }

    header.size -= 4;

    ACE_NEW_RETURN(m_RecvWPct, WorldPacket((uint16)header.cmd, header.size), -1);

    if (header.size > 0)
    {
        m_RecvWPct->resize(header.size);
        m_RecvPct.base((char*) m_RecvWPct->contents(), m_RecvWPct->size());
    }
    else
    {
        MANGOS_ASSERT(m_RecvPct.space() == 0);
    }

    return 0;
}
