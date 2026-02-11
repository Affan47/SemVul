serviceRemoved(const QString& name)
    {
        Q_UNUSED(name);
        QString serviceName = interface->service();
        QDBusReply<bool> reply = interface->connection().interface()->isServiceRegistered(serviceName);
        if (!reply.value()) {
            emit ipcFault(QService::ErrorServiceNoLongerAvailable);
        }
    }
