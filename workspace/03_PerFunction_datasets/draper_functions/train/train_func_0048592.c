formatEntry(QByteArray url, QByteArray title, qlonglong prdate)
{
    QDateTime dateTime = QDateTime::fromTime_t(prdate / 1000000);
    dateTime.addMSecs((prdate % 1000000) / 1000);
    HistoryEntry entry(url, dateTime, title);
    return entry;
}
