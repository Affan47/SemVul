paintMap(QPainter *painter, const QStyleOptionGraphicsItem * )
{
    QPointF offset = windowOffset();

    QGeoTileIterator it(this);

    while (it.hasNext()) {
        QGeoTiledMapRequest req = it.next();
        QRect tileRect = req.tileRect();

        QList<QPair<QRect, QRect> > overlaps = intersectedScreen(tileRect);
        for (int i = 0; i < overlaps.size(); ++i) {
            QRect s = overlaps.at(i).first;
            QRect t = overlaps.at(i).second;

            QRectF source = QRectF(int(s.left()) / zoomFactor,
                                   int(s.top()) / zoomFactor,
                                   int(s.width()) / zoomFactor,
                                   int(s.height()) / zoomFactor);
            QRectF target = QRectF(offset.x() + int(t.left()) / zoomFactor,
                                   offset.y() + int(t.top()) / zoomFactor,
                                   int(t.width()) / zoomFactor,
                                   int(t.height()) / zoomFactor);

            if (cache.contains(req)) {

                painter->drawImage(target, *cache.object(req), source);
            } else {
                if (zoomCache.contains(req)) {
                    painter->drawPixmap(target, *zoomCache.object(req), source);
                } else {
                    painter->fillRect(target, Qt::lightGray);
                }
            }
        }
    }
}
