event(QEvent* event)
{
    if (event->type() == QEvent::Polish && !d->content->layout()) {
        d->createLayout();
    }
    return QFrame::event(event);
}
