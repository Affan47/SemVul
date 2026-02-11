cacheFileOpenWrite()
{
    kDebug(7113);
    QString filename = cacheFilePathFromUrl(m_request.url);


    QFile *&file = m_request.cacheTag.file;
    if (file) {

        Q_ASSERT(!qobject_cast<QTemporaryFile *>(file));
        Q_ASSERT((file->openMode() & QIODevice::WriteOnly) == 0);
        Q_ASSERT(file->fileName() == filename);
        kDebug(7113) << "deleting expired cache entry and recreating.";
        file->remove();
        delete file;
        file = 0;
    }


    file = new QTemporaryFile(filename);
    file->open(QIODevice::WriteOnly);


    m_request.cacheTag.fileUseCount = 0;
    m_request.cacheTag.bytesCached = 0;

    if ((file->openMode() & QIODevice::WriteOnly) == 0) {
        kDebug(7113) << "Could not open file for writing:" << file->fileName()
                     << "due to error" << file->error();
        cacheFileClose();
        return false;
    }
    return true;
}
