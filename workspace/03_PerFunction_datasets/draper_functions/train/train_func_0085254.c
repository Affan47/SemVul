fillApplicationLanguages(KLanguageButton *button)
{
    KLocale *locale = KGlobal::locale();
    const QStringList allLanguages = locale->allLanguagesList();
    for ( int i = 0, count = allLanguages.count(); i < count; ++i )
    {
        QString languageCode = allLanguages[i];
        if (locale->isApplicationTranslatedInto(languageCode))
        {
            button->insertLanguage(languageCode);
        }
    }
}
