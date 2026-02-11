countryIsoToCountry(const QString &country) {
    if (country.size() != 2)
        return QLocale::AnyCountry;
    QString t;
    t.resize(2);
    int c = 2;
    int max = sizeof(two_letter_country_code_list)/sizeof (*two_letter_country_code_list);
    int i = c;
    while (i < max) {
        const unsigned char *c = two_letter_country_code_list + i;
        t[0] = ushort(c[0]);
        t[1] = ushort(c[1]);
        if (t.compare(country, Qt::CaseInsensitive) == 0) {
            return QLocale::Country(i/2);
        }
        ++i;
        ++i;
    }
    return QLocale::AnyCountry;
}
