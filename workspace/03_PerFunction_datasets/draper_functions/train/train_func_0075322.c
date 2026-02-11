drawTruncateText(QPainter *p, int x, int y, int maxW,
                                 const QString &t) {
    QString tmpText = p->fontMetrics().elidedText(t, Qt::ElideRight, maxW);
    p->drawText( x, y, tmpText );
}
