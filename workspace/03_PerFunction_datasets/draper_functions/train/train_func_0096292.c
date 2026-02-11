loadMovie(const QString& name, KIconLoader::Group group, int size, QObject *parent) const
{
    QString file = moviePath( name, group, size );
    if (file.isEmpty())
        return 0;
    int dirLen = file.lastIndexOf('/');
    QString icon = iconPath(name, size ? -size : group, true);
    if (!icon.isEmpty() && file.left(dirLen) != icon.left(dirLen))
        return 0;
    QMovie *movie = new QMovie(file, QByteArray(), parent);
    if (!movie->isValid())
    {
        delete movie;
        return 0;
    }
    return movie;
}
