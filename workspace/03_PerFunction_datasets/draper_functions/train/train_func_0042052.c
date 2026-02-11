initNameFromLocale(const Locale& locale, UnicodeString& result)
{
    if (locale.isBogus()) {
        result.setToBogus();
    } else {
        result.append(UnicodeString(locale.getName(), -1, US_INV));
    }
    return result;
}
