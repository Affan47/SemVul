collectInheritedServices()
{


    QSet<QString> visitedMimes;
    const QStringList allMimeTypes = m_mimeTypeFactory->allMimeTypes();
    Q_FOREACH(const QString& mimeType, allMimeTypes) {
        collectInheritedServices(mimeType, visitedMimes);
    }

}
