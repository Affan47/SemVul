eventFilter(QObject *watched, QEvent *event)
{
    if (!d->widget) {
        return false;
    }

    if (watched == d->scrollingWidget && (event->type() == QEvent::GraphicsSceneResize ||
         event->type() == QEvent::Move)) {
        emit viewportGeometryChanged(viewportGeometry());
    } else if (watched == d->widget.data() && event->type() == QEvent::GraphicsSceneResize) {
        d->stopAnimations();
        d->adjustScrollbarsTimer->start(200);
        updateGeometry();

        QPointF newPos = d->widget.data()->pos();
        if (d->widget.data()->size().width() <= viewportGeometry().width()) {
            newPos.setX(d->minXExtent());
        }
        if (d->widget.data()->size().height() <= viewportGeometry().height()) {
            newPos.setY(d->minYExtent());
        }

        if (d->widget.data()->geometry().right() < 0) {
            newPos.setX(-d->widget.data()->geometry().width()+viewportGeometry().width());
        }
        if (d->widget.data()->geometry().bottom() < 0) {
            newPos.setY(-d->widget.data()->geometry().height()+viewportGeometry().height());
        }
        d->widget.data()->setPos(newPos);

    } else if (watched == d->widget.data() && event->type() == QEvent::GraphicsSceneMove) {
        d->horizontalScrollBar->blockSignals(true);
        d->verticalScrollBar->blockSignals(true);
        d->horizontalScrollBar->setValue(-d->widget.data()->pos().x()/10);
        d->verticalScrollBar->setValue(-d->widget.data()->pos().y()/10);
        d->horizontalScrollBar->blockSignals(false);
        d->verticalScrollBar->blockSignals(false);
    }

    return false;
}
