firstDayOfYear(const QDate &date) const
{
    Q_D(const KCalendarSystem);

    if (isValid(date)) {
        return d->firstDayOfYear(year(date));
    }

    return QDate();
}
