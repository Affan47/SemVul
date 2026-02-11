eventFilter(QObject *object, QEvent *event)
{
    if (!enabled()) {
        return false;
    }

    switch (event->type())
    {
    case QEvent::MouseButtonPress:
        return mousePressEvent(object, event);
        break;
    case QEvent::MouseMove:
        if (object == _target.data()) {
            return mouseMoveEvent(object, event);
        }
        break;
    case QEvent::MouseButtonRelease:
        if (_target) {
            return mouseReleaseEvent(object, event);
        }
        break;
    default:
        break;
    }
    return false;
}
