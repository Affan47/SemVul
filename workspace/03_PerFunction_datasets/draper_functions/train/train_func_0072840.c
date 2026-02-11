dateDifference(const QDate &fromDate, const QDate &toDate,
                                     int *yearsDiff, int *monthsDiff, int *daysDiff, int *direction) const
{
    Q_D(const KCalendarSystem);

    if (isValid(fromDate) && isValid(toDate)) {
        d->dateDifference(fromDate, toDate, yearsDiff, monthsDiff, daysDiff, direction);
    }
}
