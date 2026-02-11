archiveEntries(const QString& path, const KArchiveDirectory * dir)
{
    QStringList files;
    foreach(const QString &entry, dir->entries()) {
        QString childPath = path + '/' + entry;
        if (dir->entry(entry)->isFile()) {
            files << childPath;
        }

        if (dir->entry(entry)->isDirectory()) {
            const KArchiveDirectory* childDir = static_cast<const KArchiveDirectory*>(dir->entry(entry));
            files << archiveEntries(childPath, childDir);
            files << childPath + '/';
        }
    }
    return files;
}
