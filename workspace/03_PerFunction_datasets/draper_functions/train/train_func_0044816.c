defaultAcceptList()
{
    QString currentLanguage = BrowserApplication::instance()->languageManager()->currentLanguage();
    if (currentLanguage.isEmpty())
        return QStringList();
    return expand(QLocale(currentLanguage).language());
}
