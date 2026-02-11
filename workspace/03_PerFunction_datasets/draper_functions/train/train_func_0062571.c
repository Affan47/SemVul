createDateTimeInstance(EStyle dateStyle,
                                   EStyle timeStyle,
                                   const Locale& aLocale)
{
    if(dateStyle != kNone)
    {
        dateStyle = (EStyle) (dateStyle + kDateOffset);
    }
    return create(timeStyle, dateStyle, aLocale);
}
