DoSapwnAndorovIfCan()
{
    if (GetSingleCreatureFromStorage(NPC_GENERAL_ANDOROV))
    {
        return;
    }

    Player* pPlayer = GetPlayerInMap();
    if (!pPlayer)
    {
        return;
    }

    for (uint8 i = 0; i < MAX_HELPERS; ++i)
    {
        pPlayer->SummonCreature(aAndorovSpawnLocs[i].m_uiEntry, aAndorovSpawnLocs[i].m_fX, aAndorovSpawnLocs[i].m_fY, aAndorovSpawnLocs[i].m_fZ, aAndorovSpawnLocs[i].m_fO, TEMPSUMMON_DEAD_DESPAWN, 0);
    }
}
