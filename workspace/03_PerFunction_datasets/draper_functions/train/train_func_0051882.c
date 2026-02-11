filterSearchUri(KUriFilterData &data, SearchFilterTypes types)
{
    QStringList filters;

    if (types & WebShortcutFilter)
        filters << "kurisearchfilter";

    if (types & NormalTextFilter)
        filters << "kuriikwsfilter";

    return filterUri(data, filters);
}
