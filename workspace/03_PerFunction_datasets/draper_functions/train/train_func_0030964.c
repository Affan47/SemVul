SaveToDB()
{


    CreatureData const* data = sObjectMgr.GetCreatureData(GetGUIDLow());
    if (!data)
    {
        sLog.outError("Creature::SaveToDB failed, cannot get creature data!");
        return;
    }

    SaveToDB(GetMapId(), data->spawnMask, GetPhaseMask());
}
