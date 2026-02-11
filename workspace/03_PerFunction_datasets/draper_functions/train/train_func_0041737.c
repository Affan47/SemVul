pattern(Mode mode)
{
    QStringList patterns;
    QString allPatterns;
    QString separator("|");

    const KService::List services = KServiceTypeTrader::self()->query("QImageIOPlugins");
    foreach(const KService::Ptr &service, services)
    {
        if ( (service->property("X-KDE-Read").toBool() && mode == Reading) ||
             (service->property("X-KDE-Write").toBool() && mode == Writing ) ) {

            QString mimeType = service->property("X-KDE-MimeType").toString();
            if ( mimeType.isEmpty() ) continue;
            KMimeType::Ptr mime = KMimeType::mimeType( mimeType );
            if (!mime) {
                kWarning() << service->entryPath() << " specifies unknown mimetype " << mimeType;
            } else {
                QString pattern = mime->patterns().join(" ");
                patterns.append( pattern + separator + mime->comment() );
                if (!allPatterns.isEmpty() )
                    allPatterns += ' ';
                allPatterns += pattern;
            }
        }
    }

    allPatterns = allPatterns + separator + i18n("All Pictures");
    patterns.sort();
    patterns.prepend(allPatterns);

    QString pattern = patterns.join(QLatin1String("\n"));
    return pattern;
}
