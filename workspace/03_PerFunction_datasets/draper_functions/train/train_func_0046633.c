supports( const KFileItemList &_items )
{
    if ( _items.count() != 1 )
        return false;
    bool metaDataEnabled = KGlobalSettings::showFilePreview(_items.first().url());
    if (!metaDataEnabled)
        return false;
    const KMimeType::Ptr mime = _items.first().mimeTypePtr();
    const QStringList supportedMimeTypes = KIO::PreviewJob::supportedMimeTypes();
    foreach(const QString& supportedMime, supportedMimeTypes) {
        if (mime->is(supportedMime))
    return true;
    }
    return false;
}
