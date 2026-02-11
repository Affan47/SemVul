calendarLabel(KLocale::CalendarSystem calendarSystem, const KLocale *locale)
{
    switch (calendarSystem) {
    case KLocale::QDateCalendar:
        return ki18nc("@item Calendar system", "Gregorian").toString(locale);
    case KLocale::CopticCalendar:
        return ki18nc("@item Calendar system", "Coptic").toString(locale);
    case KLocale::EthiopianCalendar:
        return ki18nc("@item Calendar system", "Ethiopian").toString(locale);
    case KLocale::GregorianCalendar:
        return ki18nc("@item Calendar system", "Gregorian (Proleptic)").toString(locale);
    case KLocale::HebrewCalendar:
        return ki18nc("@item Calendar system", "Hebrew").toString(locale);
    case KLocale::IslamicCivilCalendar:
        return ki18nc("@item Calendar system", "Islamic / Hijri (Civil)").toString(locale);
    case KLocale::IndianNationalCalendar:
        return ki18nc("@item Calendar system", "Indian National").toString(locale);
    case KLocale::JalaliCalendar:
        return ki18nc("@item Calendar system", "Jalali").toString(locale);
    case KLocale::JapaneseCalendar:
        return ki18nc("@item Calendar system", "Japanese").toString(locale);
    case KLocale::JulianCalendar:
        return ki18nc("@item Calendar system", "Julian").toString(locale);
    case KLocale::MinguoCalendar:
        return ki18nc("@item Calendar system", "Taiwanese").toString(locale);
    case KLocale::ThaiCalendar:
        return ki18nc("@item Calendar system", "Thai").toString(locale);
    }

    return ki18nc("@item Calendar system", "Invalid Calendar Type").toString(locale);
}
