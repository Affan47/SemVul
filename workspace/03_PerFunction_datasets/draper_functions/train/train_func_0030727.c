proxyScriptFileChanged(const QString& path)
    {

        Q_ASSERT(m_watcher);


        if (!m_watcher->files().isEmpty()) {
           m_watcher->removePaths(m_watcher->files());
        }


        m_watcher->addPath(path);


        m_downloader->download(KUrl::fromPath(path));
    }
