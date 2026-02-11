paintEvent(QPaintEvent *event)
{
    QToolButton::paintEvent(event);
    if (!isEnabled())
        return;

    const int pixSize = 10;
    QBrush br(d_ptr->shownColor());
    if (d_ptr->m_backgroundCheckered) {
        QPixmap pm(2 * pixSize, 2 * pixSize);
        QPainter pmp(&pm);
        pmp.fillRect(0, 0, pixSize, pixSize, Qt::white);
        pmp.fillRect(pixSize, pixSize, pixSize, pixSize, Qt::white);
        pmp.fillRect(0, pixSize, pixSize, pixSize, Qt::black);
        pmp.fillRect(pixSize, 0, pixSize, pixSize, Qt::black);
        pmp.fillRect(0, 0, 2 * pixSize, 2 * pixSize, d_ptr->shownColor());
        br = QBrush(pm);
    }

    QPainter p(this);
    const int corr = 4;
    QRect r = rect().adjusted(corr, corr, -corr, -corr);
    p.setBrushOrigin((r.width() % pixSize + pixSize) / 2 + corr, (r.height() % pixSize + pixSize) / 2 + corr);
    p.fillRect(r, br);


    const QColor frameColor1(0, 0, 0, 26);
    p.setPen(frameColor1);
    p.drawRect(r.adjusted(1, 1, -2, -2));
    const QColor frameColor2(0, 0, 0, 51);
    p.setPen(frameColor2);
    p.drawRect(r.adjusted(0, 0, -1, -1));
}
