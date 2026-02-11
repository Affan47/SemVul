eventFilter(QObject *watched, QEvent *event)
{
    switch( event->type() ) {
    case QEvent::Resize:
    case QEvent::Move:
    case QEvent::Hide:
        m_win->k_ptr->setSettingsDirty(KMainWindowPrivate::CompressCalls);
        break;

    default:
        break;
    }

    return QObject::eventFilter(watched, event);
}
