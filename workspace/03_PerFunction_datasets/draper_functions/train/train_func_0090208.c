getItemPointerByUid(const int uid) const
{

    foreach (Appointment *item, m_sortedByBeginList)
        if (item->modelUid() == uid)
            return item;
    return 0;
}
