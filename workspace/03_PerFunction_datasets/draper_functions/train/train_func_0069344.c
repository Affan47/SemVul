downloadUrl(SortMode mode) const
{
    KUrl url;
    switch (mode) {
        case Installed:
        case Rating:
            url = mDownloadUrls.value("score");
            break;
        case Alphabetical:
            url = mDownloadUrls.value(QString());
            break;
        case Updates:
        case Newest:
            url = mDownloadUrls.value("latest");
            break;
        case Downloads:
            url = mDownloadUrls.value("downloads");
            break;
    }
    if (url.isEmpty()) {
        url = mDownloadUrls.value(QString());
    }
    return url;
}
