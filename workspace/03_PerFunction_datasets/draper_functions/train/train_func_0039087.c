thresholdPosition(QPointF value) const
{
    d->minimum.setX(-d->contentsSize.width() + d->viewportGeometry.width());
    d->minimum.setY(-d->contentsSize.height() + d->viewportGeometry.height()
        -d->overshoot);

    d->minimum.setY(qMin((qreal)d->overshoot, d->minimum.y()));
    d->maximum = value;

    if(d->minimum.x() >= 0) {
        d->cposition.setX(value.x());
    } else {
        d->cposition.setX(qBound(d->minimum.x(), d->maximum.x(), qreal(0)));
    }

    if((-d->contentsSize.height() + d->viewportGeometry.height() - d->overshoot) >= 0) {
        d->cposition.setY(value.y());
    } else {
        d->cposition.setY(qBound(d->minimum.y(), d->maximum.y(), qreal(d->overshoot)));
    }

    return d->cposition;
}
