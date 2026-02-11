grammaticalNumerus(QLocale::Language language, QLocale::Country country)
{
    QStringList forms;
    getNumerusInfo(language, country, &forms);
    return forms.count();
}
