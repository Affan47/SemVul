formatDateTime(const KDateTime &fromDateTime,
                                           const QString &toFormat,
                                           KLocale::TimeFormatOptions timeOptions,
                                           const KCalendarSystem *calendar,
                                           const KLocale *locale,
                                           KLocale::DigitSet digitSet,
                                           KLocale::DateTimeFormatStandard formatStandard) const
{

    if (!fromDateTime.isValid() || !calendar->isValid(fromDateTime.date()) || toFormat.isEmpty()) {
        return QString();
    }

    if (formatStandard == KLocale::UnicodeFormat) {
        return formatDateTimeUnicode(fromDateTime, toFormat, timeOptions, calendar, locale, digitSet);
    } else {
        return formatDateTimePosix(fromDateTime, toFormat, timeOptions, calendar, locale, digitSet, formatStandard);
    }
}
