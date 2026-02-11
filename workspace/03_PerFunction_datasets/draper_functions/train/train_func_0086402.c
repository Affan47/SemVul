isAvailable()
{

    const QString &path = datapackPath();
    if (path.isEmpty())
        return false;


    QFileInfoList files = Utils::getFiles(QDir(path), "*.xml", Utils::Recursively);
    return !files.isEmpty();
}
