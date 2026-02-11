revert(const Calendar::CalendarItem &item)
{
    if (!item.isValid())
        return false;

    Appointment *pItem = getItemPointerByUid(item.uid().toInt());

    if (!pItem)
        return false;

    CalendarEventQuery query;
    query.setAppointmentId(pItem->data(Constants::Db_EvId));
    QList<Appointment *> a = base().getCalendarEvents(query);

    if (a.count()==1) {
        beginModifyItem();
        m_sortedByBeginList.removeAt(m_sortedByBeginList.indexOf(pItem));
        m_sortedByEndList.removeAt(m_sortedByEndList.indexOf(pItem));

        Appointment *newItem = a.at(0);
        m_sortedByBeginList.insert(getInsertionIndex(true, newItem->beginning(), m_sortedByBeginList, 0, m_sortedByBeginList.count() - 1), newItem);
        m_sortedByEndList.insert(getInsertionIndex(false, newItem->ending(), m_sortedByEndList, 0, m_sortedByEndList.count() - 1), newItem);

        endModifyItem(toCalendarItem(pItem), toCalendarItem(newItem));

        delete pItem;
        return true;
    }
    return false;
}
