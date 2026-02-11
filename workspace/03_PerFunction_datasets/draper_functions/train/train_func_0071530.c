setDate(QDate &date, QString eraName, int yearInEra, int month, int day) const
{
    Q_D(const KCalendarSystem);

    KCalendarEra era = d->era(eraName, yearInEra);
    return (era.isValid() && setDate(date, era.year(yearInEra), month, day));
}
