relativeLocation(const char *type, const QString &absPath)
{
    QString fullPath = absPath;
    int i = absPath.lastIndexOf(QLatin1Char('/'));
    if (i != -1) {
        fullPath = realFilePath(absPath);
    }

    const QStringList candidates = resourceDirs(type);

    for (QStringList::ConstIterator it = candidates.begin();
         it != candidates.end(); ++it) {
        if (fullPath.startsWith(*it, cs)) {
            return fullPath.mid((*it).length());
        }
    }
    return absPath;
}
