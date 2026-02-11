eventFilter(QObject *object, QEvent *e)
{
    if ( object != (QObject *)plot()->canvas() )
        return false;

    switch(e->type())
    {
        default:
            QApplication::postEvent(this, new QEvent(QEvent::User));
            break;
        case QEvent::MouseButtonPress:
            select(((QMouseEvent *)e)->pos(), true);
            break;
        case QEvent::MouseMove:
            select(((QMouseEvent *)e)->pos(), false);
            break;
    }
    return QObject::eventFilter(object, e);
}
