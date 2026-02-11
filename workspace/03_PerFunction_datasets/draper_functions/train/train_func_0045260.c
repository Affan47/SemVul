resizeEvent(QResizeEvent *event)
{
    Q_D(QVideoWidget);

    QWidget::resizeEvent(event);

    if (d->currentBackend)
        d->currentBackend->resizeEvent(event);
}
