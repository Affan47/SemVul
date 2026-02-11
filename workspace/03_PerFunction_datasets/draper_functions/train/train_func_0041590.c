LoadLootTemplates_Fishing()
{
    LootIdSet ids_set;
    LootTemplates_Fishing.LoadAndCollectLootIds(ids_set);


    for (uint32 i = 1; i < sAreaStore.GetNumRows(); ++i)
    {
        if (AreaTableEntry const* areaEntry = sAreaStore.LookupEntry(i))
            if (ids_set.find(areaEntry->ID) != ids_set.end())
                ids_set.erase(areaEntry->ID);
    }


    ids_set.erase(0);


    LootTemplates_Fishing.ReportUnusedIds(ids_set);
}
