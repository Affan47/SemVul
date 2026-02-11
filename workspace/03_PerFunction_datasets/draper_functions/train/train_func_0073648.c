HandleChannelMuteOpcode(WorldPacket& recvPacket)
{
    DEBUG_LOG("WORLD: Received opcode %s (%u, 0x%X)", recvPacket.GetOpcodeName(), recvPacket.GetOpcode(), recvPacket.GetOpcode());

    std::string channelname, otp;
    recvPacket >> channelname;

    recvPacket >> otp;

    if (!normalizePlayerName(otp))
        { return; }

    if (ChannelMgr* cMgr = channelMgr(_player->GetTeam()))
        if (Channel* chn = cMgr->GetChannel(channelname, _player))
        {
            chn->SetMute(_player, otp.c_str());
        }
}
