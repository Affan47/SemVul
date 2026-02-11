findInCache(const QString &key, unsigned int lastModified)
{
    if (cacheRendering) {
        QString cache = cachePath(key);
        if (QFile::exists(cache)) {
            if (lastModified > 0) {
                QFileInfo info(cache);
                if (info.lastModified().toTime_t() < lastModified) {
                    return false;
                }
            }

            LoadImageThread *loadImageT = new LoadImageThread(cache);
            q->connect(loadImageT, SIGNAL(done(QImage)), q, SIGNAL(renderCompleted(QImage)));
            QThreadPool::globalInstance()->start(loadImageT);

            return true;
        }
    }

    return false;
}
