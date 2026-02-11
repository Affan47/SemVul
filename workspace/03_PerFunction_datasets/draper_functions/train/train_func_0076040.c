setNameFilter( const QString& nameFilter )
{
    if (d->nameFilter == nameFilter)
        return;

    d->prepareForSettingsChange();

    d->settings.lstFilters.clear();
    d->nameFilter = nameFilter;

    const QStringList list = nameFilter.split( ' ', QString::SkipEmptyParts );
    for (QStringList::const_iterator it = list.begin(); it != list.end(); ++it)
        d->settings.lstFilters.append(QRegExp(*it, Qt::CaseInsensitive, QRegExp::Wildcard));
}
