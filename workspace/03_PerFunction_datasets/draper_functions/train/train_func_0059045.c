SpawnBGCreature(ObjectGuid guid, uint32 respawntime)
{
    Map* map = GetBgMap();

    Creature* obj = map->GetCreature(guid);
    if (!obj)
        return;
    if (respawntime == 0)
    {
        obj->Respawn();
        map->Add(obj);
    }
    else
    {
        map->Add(obj);
        obj->SetRespawnDelay(respawntime);
        obj->SetDeathState(JUST_DIED);
        obj->RemoveCorpse();
    }
}
