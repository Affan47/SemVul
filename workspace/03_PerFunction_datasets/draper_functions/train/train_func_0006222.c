firstDateInNextPeriod(const QDate& date, QOrganizerRecurrenceRule::Frequency frequency, Qt::DayOfWeek firstDayOfWeek) const
{
    QDate retn(date);
    switch (frequency) {
        case QOrganizerRecurrenceRule::Yearly:
            retn.setDate(date.year()+1, 1, 1);
            return retn;
        case QOrganizerRecurrenceRule::Monthly:
            {
            int newMonth = date.month() + 1;
            int newYear = date.year() + (newMonth==13 ? 1 : 0);
            retn.setDate(newYear, newMonth==13 ? 1 : newMonth, 1);
            }
            return retn;
        case QOrganizerRecurrenceRule::Weekly:
            do {
                retn = retn.addDays(1);
            } while (retn.dayOfWeek() != firstDayOfWeek);
            return retn;
        case QOrganizerRecurrenceRule::Daily:
            retn = retn.addDays(1);
            return retn;
        case QOrganizerRecurrenceRule::Invalid:
            Q_ASSERT(false);
    }
    return retn;
}
