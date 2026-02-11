SortTemplates(long item1, long item2, cb_unused long sortData)
#endif
{
    ListItemData* data1 = reinterpret_cast<ListItemData*>(item1);
    ListItemData* data2 = reinterpret_cast<ListItemData*>(item2);

    if (!data1 && data2)
        return 1;
    if (data1 && !data2)
        return -1;
    if (data1 && data2)
    {
        wxString name1 = data1->pt ? data1->pt->m_Title : data1->plugin->GetTitle(data1->wizPluginIndex);
        wxString name2 = data2->pt ? data2->pt->m_Title : data2->plugin->GetTitle(data2->wizPluginIndex);

        return name1.CompareTo(name2);
    }
    return 0;
}
