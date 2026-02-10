_k_resolveSymLink(const QString &filename)
{
    QString resolved = filename;
    QString tmp = QFile::symLinkTarget(filename);

    while (!tmp.isEmpty()) {
        resolved = tmp;
        tmp = QFile::symLinkTarget(resolved);
    }

    return resolved;
}
