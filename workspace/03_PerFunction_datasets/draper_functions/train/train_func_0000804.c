getFiles(QDir fromDir, const QStringList &filters, DirSearchType recursive)
{
    QFileInfoList files;

    if (!fromDir.exists())
        return files;
    if (fromDir.path() == ".")
        return files;

    foreach (const QFileInfo & file, fromDir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot, QDir::DirsFirst | QDir::Name)) {
        if (file.isFile() && (filters.isEmpty() || QDir::match(filters, file.fileName())))
            files << file;
        else if (file.isDir() && recursive==Recursively) {
            fromDir.cd(file.filePath());
            files << getFiles(fromDir, filters, recursive);
            fromDir.cdUp();
        }
    }
    return files;
}
