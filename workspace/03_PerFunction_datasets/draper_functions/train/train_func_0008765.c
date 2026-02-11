setDtFromUtc(const QDateTime &utcdt)
{
    switch (specType)
    {
        case KDateTime::UTC:
            setDt(utcdt);
            break;
        case KDateTime::OffsetFromUTC:
        {
            QDateTime local = utcdt.addSecs(specUtcOffset);
            local.setTimeSpec(Qt::LocalTime);
            setDt(local, utcdt);
            break;
        }
        case KDateTime::TimeZone:
        {
            bool second;
            setDt(specZone.toZoneTime(utcdt, &second), utcdt);
            m2ndOccurrence = second;
            break;
        }
        case KDateTime::ClockTime:
            specZone = KSystemTimeZones::local();
            setDt(specZone.toZoneTime(utcdt), utcdt);
            break;
        default:
            break;
    }
}
