setCurrentCountry(QLocale::Country country)
{
    setCurrentIndex(findData(QVariant(country)));
}
