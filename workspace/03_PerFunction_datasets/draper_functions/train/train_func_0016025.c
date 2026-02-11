eventFilter(QObject *obj, QEvent *event)
{
    switch (event->type()) {
    case QEvent::MouseButtonPress:
    case QEvent::MouseButtonRelease:
    case QEvent::MouseButtonDblClick:
    case QEvent::KeyPress:
    case QEvent::KeyRelease:
    case QEvent::Wheel:
    case QEvent::DragEnter:
    case QEvent::DragMove:
    case QEvent::DragLeave:
    case QEvent::Drop:
    case QEvent::ContextMenu:
    case QEvent::TabletPress:
    case QEvent::TabletRelease:


        d->_timer.start();
        break;
    default: break;
    }
    return QObject::eventFilter(obj, event);
}
