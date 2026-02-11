downloadResource (const KUrl& srcUrl, const QString& suggestedName = QString(),
                              QWidget* parent = 0, const KIO::MetaData& metaData = KIO::MetaData())
{
    const QString fileName = suggestedName.isEmpty() ? srcUrl.fileName() : suggestedName;

    KUrl destUrl = KFileDialog::getSaveFileName(KUrl::fromPath(fileName), QString(), parent);
    if (!destUrl.isValid())
        return false;


    KIO::Job *job = KIO::copy(srcUrl, destUrl);

    if (!metaData.isEmpty())
        job->setMetaData(metaData);

    job->addMetaData(QL1S("MaxCacheSize"), QL1S("0"));
    job->addMetaData(QL1S("cache"), QL1S("cache"));
    job->ui()->setWindow((parent ? parent->window() : 0));
    job->ui()->setAutoErrorHandlingEnabled(true);
    return true;
}
