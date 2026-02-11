dateChanged(int month, int year)
{
    if (!isVisible()) {
        stale = true;
        return;
    }

    setUpdatesEnabled(false);


    QDate date(year,month,01);
    calendars.at(0)->setDate(month, year);
    for (int i=1; i<calendars.count();i++) {
        QDate ours = date.addMonths(i);
        calendars.at(i)->setDate(ours.month(), ours.year());
    }
    setUpdatesEnabled(true);
}
