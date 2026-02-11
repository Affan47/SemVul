shuffle()
{
    Q_D(QLocalMediaPlaylistProvider);
    if (!d->resources.isEmpty()) {
        QList<QMediaContent> resources;

        while (!d->resources.isEmpty()) {
            resources.append(d->resources.takeAt(qrand() % d->resources.size()));
        }

        d->resources = resources;
        emit mediaChanged(0, mediaCount()-1);
    }

}
