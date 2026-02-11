get(const QString &name, const QSize &render_size)
{
    QSize size;
    QStringList itemList = name.split('#');

    QString svgFile = d->fileHash[itemList.value(0)];
    QFileInfo fileInfo (svgFile);

    if (fileInfo.exists()) {
        d->render.load(svgFile);
    }

    if (render_size == QSize()) {

        QRectF elementBounds = d->render.boundsOnElement(itemList.value(1));
        size.setWidth(elementBounds.width());
        size.setHeight(elementBounds.height());
    } else
        size = render_size;

    QPixmap rv (size);

    if (itemList.count() < 1) {
      return rv;
    } else if (itemList.count() == 1) {
      return d->map[name];
    }

    rv.fill(Qt::transparent);
    QPainter painter;

    painter.begin(&rv);

    drawSvg(&painter, QRectF (0.0, 0.0, size.width(), size.height()),
        svgFile, itemList.value(1));

    painter.end();

    return rv;
}
