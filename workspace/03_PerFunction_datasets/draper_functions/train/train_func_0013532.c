downloadedUrl(const QUrl &url)
    {
        foreach(const DownloadedUrl &dld, _downloadedUrl) {
            if (dld.url == url)
                return dld;
        }
        return _emptyDownloaded;
    }
