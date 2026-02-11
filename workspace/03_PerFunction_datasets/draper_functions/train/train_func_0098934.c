BuildPacket(WorldPacket *packet)
{
    MANGOS_ASSERT(packet->empty());

    ByteBuffer buf(4 + (m_outOfRangeGUIDs.empty() ? 0 : 1 + 4 + 9 * m_outOfRangeGUIDs.size()) + m_data.wpos());

    buf << (uint32) (!m_outOfRangeGUIDs.empty() ? m_blockCount + 1 : m_blockCount);

    if(!m_outOfRangeGUIDs.empty())
    {
        buf << (uint8) UPDATETYPE_OUT_OF_RANGE_OBJECTS;
        buf << (uint32) m_outOfRangeGUIDs.size();

        for(ObjectGuidSet::const_iterator i = m_outOfRangeGUIDs.begin(); i != m_outOfRangeGUIDs.end(); ++i)
            buf << i->WriteAsPacked();
    }

    buf.append(m_data);

    size_t pSize = buf.wpos();

    if (pSize > 100 )
    {
        uint32 destsize = compressBound(pSize);
        packet->resize( destsize + sizeof(uint32) );

        packet->put<uint32>(0, pSize);
        Compress(const_cast<uint8*>(packet->contents()) + sizeof(uint32), &destsize, (void*)buf.contents(), pSize);
        if (destsize == 0)
            return false;

        packet->resize( destsize + sizeof(uint32) );
        packet->SetOpcode( SMSG_COMPRESSED_UPDATE_OBJECT );
    }
    else
    {
        packet->append( buf );
        packet->SetOpcode( SMSG_UPDATE_OBJECT );
    }

    return true;
}
