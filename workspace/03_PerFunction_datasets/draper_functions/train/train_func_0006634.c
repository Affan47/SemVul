insertItem(const std::string &luid, const std::string &item)
{
    StringPair ids = splitLUID(luid);
    SubSyncSource::SubItemResult res = m_sub->insertSubItem(ids.first, ids.second, item);

    if (res.m_state != ITEM_NEEDS_MERGE) {
        SubRevisionEntry &entry = m_revisions[res.m_mainid];
        entry.m_uid = res.m_uid;
        entry.m_revision = res.m_revision;
        entry.m_subids.insert(res.m_subid);
    }
    return SyncSourceRaw::InsertItemResult(createLUID(res.m_mainid, res.m_subid),
                                           res.m_revision, res.m_state);
}
