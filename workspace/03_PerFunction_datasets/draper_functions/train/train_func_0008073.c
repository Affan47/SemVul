Respawn()
{
    RemoveCorpse();
    if (!IsInWorld())
        { return; }

    if (IsDespawned())
    {
        if (HasStaticDBSpawnData())
            { GetMap()->GetPersistentState()->SaveCreatureRespawnTime(GetGUIDLow(), 0); }
        m_respawnTime = time(NULL);
    }
}
