Respawn()
{
    if (m_spawnedByDefault && m_respawnTime > 0)
    {
        m_respawnTime = time(NULL);
        GetMap()->GetPersistentState()->SaveGORespawnTime(GetGUIDLow(), 0);
    }
}
