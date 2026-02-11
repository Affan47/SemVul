CheckLootRefs(LootIdSet* ref_set) const
{
    for (LootStoreItemList::const_iterator ieItr = Entries.begin(); ieItr != Entries.end(); ++ieItr)
    {
        if (ieItr->mincountOrRef < 0)
        {
            if (!LootTemplates_Reference.GetLootFor(-ieItr->mincountOrRef))
                { LootTemplates_Reference.ReportNotExistedId(-ieItr->mincountOrRef); }
            else if (ref_set)
                { ref_set->erase(-ieItr->mincountOrRef); }
        }
    }

    for (LootGroups::const_iterator grItr = Groups.begin(); grItr != Groups.end(); ++grItr)
        { grItr->CheckLootRefs(ref_set); }
}
