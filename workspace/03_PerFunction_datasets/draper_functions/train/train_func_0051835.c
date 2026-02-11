RemoveCorpse()
{

    if (uint16 poolid = sPoolMgr.IsPartOfAPool<Creature>(GetGUIDLow()))
        sPoolMgr.UpdatePool<Creature>(*GetMap()->GetPersistentState(), poolid, GetGUIDLow());

    if (!IsInWorld())
        return;

    if ((getDeathState() != CORPSE && !m_isDeadByDefault) || (getDeathState() != ALIVE && m_isDeadByDefault))
        return;

    DEBUG_FILTER_LOG(LOG_FILTER_AI_AND_MOVEGENSS, "Removing corpse of %s ", GetGuidStr().c_str());

    m_corpseDecayTimer = 0;
    SetDeathState(DEAD);
    UpdateObjectVisibility();


    StopGroupLoot();

    loot.clear();
    uint32 respawnDelay = 0;

    if (AI())
        AI()->CorpseRemoved(respawnDelay);

    if (m_isCreatureLinkingTrigger)
        GetMap()->GetCreatureLinkingHolder()->DoCreatureLinkingEvent(LINKING_EVENT_DESPAWN, this);


    if (respawnDelay)
        m_respawnTime = time(NULL) + respawnDelay;

    float x, y, z, o;
    GetRespawnCoord(x, y, z, &o);
    GetMap()->CreatureRelocation(this, x, y, z, o);


    UnitVisibility currentVis = GetVisibility();
    SetVisibility(VISIBILITY_REMOVE_CORPSE);
    UpdateObjectVisibility();
    SetVisibility(currentVis);
    UpdateObjectVisibility();
}
