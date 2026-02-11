SetCreatureRespawnTime(uint32 loguid, time_t t)
{
    if (t > sWorld.GetGameTime())
        m_creatureRespawnTimes[loguid] = t;
    else
    {
        m_creatureRespawnTimes.erase(loguid);
        UnloadIfEmpty();
    }
}
