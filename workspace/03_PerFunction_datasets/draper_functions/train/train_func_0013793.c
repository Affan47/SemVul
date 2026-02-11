convertToOptions(KConfig::WriteConfigFlags flags)
{
    KEntryMap::EntryOptions options=0;

    if (flags&KConfig::Persistent)
        options |= KEntryMap::EntryDirty;
    if (flags&KConfig::Global)
        options |= KEntryMap::EntryGlobal;
    if (flags&KConfig::Localized)
        options |= KEntryMap::EntryLocalized;
    return options;
}
