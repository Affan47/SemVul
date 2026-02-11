paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    int intRotation = int(d->rotation);

    QRectF spinnerRect(QPoint(0, 0), QSize(qMin(size().width(), size().height()), qMin(size().width(), size().height())));
    spinnerRect.moveCenter(boundingRect().center());

    if (!isEnabled()) {
        painter->setOpacity(painter->opacity() / 2);
    }

    if (!d->running && d->svg->hasElement("paused")) {
        d->svg->paint(painter, spinnerRect, "paused");
    } else {
        if (!d->frames[intRotation]) {
            QPointF translatedPos(spinnerRect.width()/2, spinnerRect.height()/2);

            d->frames[intRotation] = QPixmap(spinnerRect.size().toSize());
            d->frames[intRotation].fill(Qt::transparent);

            QPainter buffPainter(&d->frames[intRotation]);

            buffPainter.setRenderHints(QPainter::SmoothPixmapTransform);
            buffPainter.translate(translatedPos);

            if (d->svg->hasElement("busywidget-shadow")) {
                buffPainter.save();
                buffPainter.translate(1,1);
                buffPainter.rotate(intRotation);
                d->svg->paint(&buffPainter, QRectF(-translatedPos.toPoint(), spinnerRect.size()), "busywidget-shadow");
                buffPainter.restore();
            }

            buffPainter.rotate(intRotation);
            d->svg->paint(&buffPainter, QRectF(-translatedPos.toPoint(), spinnerRect.size()), "busywidget");
        }

        painter->drawPixmap(spinnerRect.topLeft().toPoint(), d->frames[intRotation]);
    }

    painter->setPen(Plasma::Theme::defaultTheme()->color(Theme::TextColor));
    Qt::Alignment align(Qt::AlignVCenter | Qt::AlignHCenter);
    painter->drawText(boundingRect(), d->label, QTextOption(align));
}
