update(KNotification * n, int id)
{
	if(id <= 0)
		return;

    QByteArray pixmapData;
    if(!n->pixmap().isNull())
    {
        QBuffer buffer(&pixmapData);
        buffer.open(QIODevice::WriteOnly);
        n->pixmap().save(&buffer, "PNG");
    }

    d->knotify->update(id, n->title(), n->text(), pixmapData , n->actions() );
}
