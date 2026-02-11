SendUpdateWorldState(uint32 field, uint32 value)
{
    for (GuidZoneMap::const_iterator itr = m_zonePlayers.begin(); itr != m_zonePlayers.end(); ++itr)
    {

        if (!itr->second)
            continue;

        if (Player* player = sObjectMgr.GetPlayer(itr->first))
            player->SendUpdateWorldState(field, value);
    }
}
