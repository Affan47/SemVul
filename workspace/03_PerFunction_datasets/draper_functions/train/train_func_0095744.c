findFromFileName(const QString &fileName, QString *pMatchingExtension)
{
    m_mutex.lockForWrite();
    parseGlobs();
    m_mutex.unlock();

    QReadLocker lock(&m_mutex);

    QStringList matchingMimeTypes;
    QString foundExt;
    findFromOtherPatternList(matchingMimeTypes, fileName, foundExt, true);
    if (matchingMimeTypes.isEmpty()) {


        const int lastDot = fileName.lastIndexOf(QLatin1Char('.'));
        if (lastDot != -1) {
            const int ext_len = fileName.length() - lastDot - 1;
            const QString simpleExtension = fileName.right( ext_len ).toLower();


            matchingMimeTypes = m_globs.m_fastPatterns.value(simpleExtension);
            if (!matchingMimeTypes.isEmpty()) {
                foundExt = simpleExtension;


            }
        }


        findFromOtherPatternList(matchingMimeTypes, fileName, foundExt, false);
    }
    if (pMatchingExtension)
        *pMatchingExtension = foundExt;
    return matchingMimeTypes;
}
