drawSvg(QPainter *p, QRectF rect, const QString &file, const QString &elementId)
{
    QString svgFile = d->fileHash[file];
    qDebug() << Q_FUNC_INFO << svgFile;
    QFileInfo fileInfo (svgFile);
    if (fileInfo.exists()) {
        d->render.load(svgFile);
        d->render.render(p, elementId,  rect);
        return true;
    }

    return false;
}
