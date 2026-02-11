paintEvent(QPaintEvent *event)
{
    Q_D(QVideoWidget);

    if (d->currentBackend) {
        d->currentBackend->paintEvent(event);
    } else if (testAttribute(Qt::WA_OpaquePaintEvent)) {
        QPainter painter(this);

        painter.fillRect(event->rect(), palette().window());
    }
}
