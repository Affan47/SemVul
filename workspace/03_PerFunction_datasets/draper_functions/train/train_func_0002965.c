abort()
{
    close();
    if (!d->tempFileName.isEmpty()) {
        QFile::remove(d->tempFileName);
        d->needFinalize = false;
    }
}
