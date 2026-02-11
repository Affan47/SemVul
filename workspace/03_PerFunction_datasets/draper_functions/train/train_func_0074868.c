HasQuestDrop(LootTemplateMap const& store, uint8 groupId) const
{
    if (groupId)
    {
        if (groupId > Groups.size())
            return false;
        return Groups[groupId - 1].HasQuestDrop();
    }

    for (LootStoreItemList::const_iterator i = Entries.begin(); i != Entries.end(); ++i)
    {
        if (i->mincountOrRef < 0)
        {
            LootTemplateMap::const_iterator Referenced = store.find(-i->mincountOrRef);
            if (Referenced == store.end())
                continue;
            if (Referenced->second->HasQuestDrop(store, i->group))
                return true;
        }
        else if (i->needs_quest)
            return true;
    }


    for (LootGroups::const_iterator i = Groups.begin() ; i != Groups.end() ; ++i)
        if (i->HasQuestDrop())
            return true;

    return false;
}
