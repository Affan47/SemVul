SendForceReactions()
{
    WorldPacket data;
    data.Initialize(SMSG_SET_FORCED_REACTIONS, 4 + m_forcedReactions.size() * (4 + 4));
    data << uint32(m_forcedReactions.size());
    for (ForcedReactions::const_iterator itr = m_forcedReactions.begin(); itr != m_forcedReactions.end(); ++itr)
    {
        data << uint32(itr->first);
        data << uint32(itr->second);
    }
    m_player->SendDirectMessage(&data);
}
