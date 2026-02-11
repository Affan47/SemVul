eventFilter(QObject *watched, QEvent *event)
{
    QGraphicsWidget *targetWidget = static_cast<QGraphicsWidget *>(d->target);
    if (watched == targetWidget) {
        if (event->type() == QEvent::GraphicsSceneResize ||
            event->type() == QEvent::GraphicsSceneMove) {

            QTimer::singleShot(0, this, SLOT(refreshCurrentTarget()) );
        } else if (event->type() == QEvent::Show) {
            setTargetItem(targetWidget);
        }
    }

    return false;
}
