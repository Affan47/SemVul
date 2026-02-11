threadConnection()
{
    if (QCoreApplication::instance()->thread() == QThread::currentThread()) {
        return QDBusConnection::sessionBus();
    }
    if (!s_perThreadConnection.hasLocalData()) {
        s_perThreadConnection.setLocalData(new KDBusConnectionPoolPrivate);
    }

    return s_perThreadConnection.localData()->connection();
}
