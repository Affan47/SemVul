HandleLeaveChannelOpcode(WorldPacket& recvPacket)
{
    DEBUG_LOG("WORLD: Received opcode %s (%u, 0x%X)", recvPacket.GetOpcodeName(), recvPacket.GetOpcode(), recvPacket.GetOpcode());


    uint32 unk;
    std::string channelname;
    recvPacket >> unk;
    recvPacket >> channelname;

    if (channelname.empty())
        return;

    if (ChannelMgr* cMgr = channelMgr(_player->GetTeam()))
    {
        if (Channel* chn = cMgr->GetChannel(channelname, _player))
            chn->Leave(_player, true);
        cMgr->LeftChannel(channelname);
    }
}
