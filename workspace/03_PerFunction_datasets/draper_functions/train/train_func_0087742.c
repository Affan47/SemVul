findAllResources( const char *type,
                                 const QString& filter,
                                 SearchOptions options,
                                 QStringList &relList) const
{
    QString filterPath;
    QString filterFile;

    if ( !filter.isEmpty() )
    {
        int slash = filter.lastIndexOf(QLatin1Char('/'));
        if (slash < 0) {
            filterFile = filter;
        } else {
            filterPath = filter.left(slash + 1);
            filterFile = filter.mid(slash + 1);
        }
    }

    QStringList candidates;
    if ( !QDir::isRelativePath(filter) )
    {
#ifdef Q_OS_WIN
        candidates << filterPath.left(3);
        filterPath = filterPath.mid(3);
#else
        candidates << QString::fromLatin1("/");
        filterPath = filterPath.mid(1);
#endif
    }
    else
    {
        candidates = d->resourceDirs(type, filter);
    }

    if (filterFile.isEmpty()) {
        filterFile = QString(QLatin1Char('*'));
    }

    QRegExp regExp(filterFile, Qt::CaseSensitive, QRegExp::Wildcard);

    QStringList list;
    foreach ( const QString& candidate, candidates )
    {
        lookupPrefix(candidate, filterPath, QString(), regExp, list,
                     relList, options & Recursive, options & NoDuplicates);
    }

    return list;
}
