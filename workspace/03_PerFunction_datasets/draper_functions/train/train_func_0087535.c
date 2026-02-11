eventFilter (QObject *o, QEvent *e) {
    if (m_liveconnect->jsSessions () > 0) {
        switch (e->type()) {
            case QEvent::Destroy:
            case QEvent::Close:
            case QEvent::Quit:
                return true;
            default:
                break;
        }
    }
    return KParts::ReadOnlyPart::eventFilter(o,e);
}
