event( QEvent* ev )
{
    bool ret = KMainWindow::event(ev);
    if (ev->type()==QEvent::Polish) {
        QDBusConnection::sessionBus().registerObject(dbusName() + "/actions", actionCollection(),
                                                     QDBusConnection::ExportScriptableSlots |
                                                     QDBusConnection::ExportScriptableProperties |
                                                     QDBusConnection::ExportNonScriptableSlots |
                                                     QDBusConnection::ExportNonScriptableProperties |
                                                     QDBusConnection::ExportChildObjects);
    }
    return ret;
}
