setModified(bool modified)
{
    m_Modified = modified;
    if (!modified) {
        QList<int> keys;
        keys << ID_UserName << ID_EpisodeLabel << ID_EpisodeDate << ID_Priority;
        foreach(int id, keys) {
            m_OriginalData.insert(id, data(id));
        }
    }
}
