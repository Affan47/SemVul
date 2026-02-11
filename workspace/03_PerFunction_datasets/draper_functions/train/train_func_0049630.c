loadConfig(const QString & calendarType)
{
    KConfigGroup localeGroup(config(), QString::fromLatin1("Locale"));
    KConfigGroup calendarGroup = localeGroup.group(QString::fromLatin1("KCalendarSystem %1").arg(calendarType));
    loadEraList(calendarGroup);
    loadShortYearWindowStartYear(calendarGroup);
}
