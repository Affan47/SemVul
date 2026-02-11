loadDefaultEraList()
{
    QString name, shortName, format;

    name = i18nc("Calendar Era: Indian National Saka Era, years > 0, LongFormat", "Saka Era");
    shortName = i18nc("Calendar Era: Indian National Saka Era, years > 0, ShortFormat", "SE");
    format = i18nc("(kdedt-format) Indian National, SE, full era year format used for %EY, e.g. 2000 SE", "%Ey %EC");
    addEra('+', 1, q->epoch(), 1, q->latestValidDate(), name, shortName, format);
}
