GetBattleGroundThroughClientInstance(uint32 instanceId, BattleGroundTypeId bgTypeId)
{


    BattleGround* bg = GetBattleGroundTemplate(bgTypeId);
    if (!bg)
        { return NULL; }

    for (BattleGroundSet::iterator itr = m_BattleGrounds[bgTypeId].begin(); itr != m_BattleGrounds[bgTypeId].end(); ++itr)
    {
        if (itr->second->GetClientInstanceID() == instanceId)
            { return itr->second; }
    }
    return NULL;
}
