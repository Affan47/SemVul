displayText(const QVariant &value, const QLocale &locale) const
{
    if (m_IsDateOnly)
        return locale.toString(value.toDate(), tkTr(Trans::Constants::DATEFORMAT_FOR_EDITOR));
    return locale.toString(value.toDateTime(), tkTr(Trans::Constants::DATETIMEFORMAT_FOR_EDITOR));
}
