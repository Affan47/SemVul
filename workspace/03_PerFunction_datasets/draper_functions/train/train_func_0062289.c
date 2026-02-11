isDeleted(QString path)
{
    if (fileMap->contains(path)) {
        return (!QFileInfo(path).exists());
    } else
        return false;
}
