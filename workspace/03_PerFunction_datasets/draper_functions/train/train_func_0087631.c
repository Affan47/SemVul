PlayDirectSoundToMap(uint32 soundId, uint32 zoneId ) const
{
    WorldPacket data(SMSG_PLAY_SOUND, 4);
    data << uint32(soundId);

    Map::PlayerList const& pList = GetPlayers();
    for (PlayerList::const_iterator itr = pList.begin(); itr != pList.end(); ++itr)
        if (!zoneId || itr->getSource()->GetZoneId() == zoneId)
            itr->getSource()->SendDirectMessage(&data);
}
