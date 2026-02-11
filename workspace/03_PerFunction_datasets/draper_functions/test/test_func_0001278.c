updateCatalogs()
{


    QList<KCatalog> newCatalogs;


    foreach(const QString &lang, m_languageList) {
        if (lang == KLocale::defaultLanguage()) {


            break;
        }
        foreach(const KCatalogName &name, m_catalogNames) {

            if (! KCatalog::catalogLocaleDir(name.name, lang).isEmpty()) {
                newCatalogs.append(KCatalog(name.name, lang));

            }
        }
    }


    m_catalogs = newCatalogs;
    KLocalizedString::notifyCatalogsUpdated(m_languageList, m_catalogNames);
}
