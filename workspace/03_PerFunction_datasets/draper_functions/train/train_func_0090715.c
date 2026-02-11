DoToggleGameObjectFlags(uint32 uiEntry, uint32 uiGOflags, bool bApply)
{
    EntryGuidMap::iterator find = m_mGoEntryGuidStore.find(uiEntry);
    if (find != m_mGoEntryGuidStore.end())
    {
        DoToggleGameObjectFlags(find->second, uiGOflags, bApply);
    }
    else

    {
        debug_log("SD2: Script call ToogleTameObjectFlags (by Entry), but no gameobject of entry %u was created yet, or it was not stored by script for map %u.", uiEntry, instance->GetId());
    }
}
