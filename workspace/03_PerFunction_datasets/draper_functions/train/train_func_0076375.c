setData(const int ref, const QVariant &value)
{
    d->m_Data.insert(ref, value);

    if (ref == Uid) {
        foreach(PmhEpisodeData *ep, d->m_Episodes) {
            ep->setData(PmhEpisodeData::DbOnly_MasterId, value);
        }
    }
    return true;
}
