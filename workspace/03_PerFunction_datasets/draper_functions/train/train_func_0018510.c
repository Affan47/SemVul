writePathEntry(const QString& pKey, const QString & path, WriteConfigFlags pFlags)
{
    writePathEntry(pKey.toUtf8().constData(), path, pFlags);
}
