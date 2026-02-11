icon(const QUrl &url)
{
    QIcon icon = QWebSettings::iconForUrl(url);
    if (!icon.isNull())
        return icon.pixmap(16, 16);
    if (icon.isNull()) {
        QPixmap pixmap = QWebSettings::webGraphic(QWebSettings::DefaultFrameIconGraphic);
        if (pixmap.isNull()) {
            pixmap = QPixmap(QLatin1String(":graphics/defaulticon.png"));
            QWebSettings::setWebGraphic(QWebSettings::DefaultFrameIconGraphic, pixmap);
        }
        return pixmap;
    }
    return icon;
}
