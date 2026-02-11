checkDesktopFile(const KFileItem& item, bool _determineMimeType)
{

    bool isLocal;
    const KUrl url = item.mostLocalUrl(isLocal);
    if (!isLocal)
        return false;


    if (!item.isRegularFile())
        return false;


    if (!item.isReadable())
        return false;


    KMimeType::Ptr mime = _determineMimeType ? item.determineMimeType() : item.mimeTypePtr();
    return mime->is("application/x-desktop");
}
