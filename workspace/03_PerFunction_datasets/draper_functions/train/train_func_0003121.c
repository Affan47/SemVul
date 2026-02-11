setData(const Calendar::CalendarItem &item, int dataRef, const QVariant &value, int role)
{
    if (!item.isValid())
        return false;

    if (dataRef==Uid)
        return false;

    Appointment *pItem = getItemPointerByUid(item.uid().toInt());

    if (!pItem)
        return false;

    if (pItem->data(dataRef) == value)
        return true;


    if (role==Qt::EditRole) {
        pItem->setData(dataRef, value);
        if (dataRef==DateStart || dataRef==DateEnd) {
            Q_EMIT itemModified(item, toCalendarItem(pItem));
        }
        Q_EMIT dataChanged(item);
        return true;
    }

    return false;
}
