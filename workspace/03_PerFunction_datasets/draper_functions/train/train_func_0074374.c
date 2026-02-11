readXml(QIODevice* device, const QDir& directory)
{
    return readXml(device, QStringList(directory.absolutePath()));
}
