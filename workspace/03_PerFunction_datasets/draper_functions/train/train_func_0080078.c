event(QEvent *event)
{
    Q_D(QVideoWidget);

    if (event->type() == QEvent::WindowStateChange) {
        Qt::WindowFlags flags = windowFlags();

        if (windowState() & Qt::WindowFullScreen) {
            if (d->currentControl)
                d->currentControl->setFullScreen(true);

            if (!d->wasFullScreen)
                emit fullScreenChanged(d->wasFullScreen = true);
        } else {
            if (d->currentControl)
                d->currentControl->setFullScreen(false);

            if (d->wasFullScreen) {
                flags &= ~(Qt::Window | Qt::SubWindow);
                flags |= d->nonFullScreenFlags;
                setWindowFlags(flags);

                emit fullScreenChanged(d->wasFullScreen = false);
            }
        }
    }
    return QWidget::event(event);
}
