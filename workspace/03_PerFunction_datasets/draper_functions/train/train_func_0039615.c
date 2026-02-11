slotServiceRegistered(const QString &serviceName)
{
    if (serviceName == QLatin1String("org.freedesktop.PowerManagement")) {

        QDBusPendingReply<bool> suspendReply = managerIface.CanSuspend();
        suspendReply.waitForFinished();
        slotCanSuspendChanged(suspendReply.isValid() ? suspendReply.value() : false);

        QDBusPendingReply<bool> hibernateReply = managerIface.CanHibernate();
        hibernateReply.waitForFinished();
        slotCanHibernateChanged(hibernateReply.isValid() ? hibernateReply.value() : false);

        QDBusPendingReply<bool> hybridSuspendReply = managerIface.CanHybridSuspend();
        hybridSuspendReply.waitForFinished();
        slotCanHybridSuspendChanged(hybridSuspendReply.isValid() ? hybridSuspendReply.value() : false);

        QDBusPendingReply<bool> saveStatusReply = managerIface.GetPowerSaveStatus();
        saveStatusReply.waitForFinished();
        slotPowerSaveStatusChanged(saveStatusReply.isValid() ? saveStatusReply.value() : false);
    } else {

        QDBusMessage call = QDBusMessage::createMethodCall(QLatin1String("org.kde.Solid.PowerManagement"),
                                                           QLatin1String("/org/kde/Solid/PowerManagement"),
                                                           QLatin1String("org.kde.Solid.PowerManagement"),
                                                           QLatin1String("backendCapabilities"));
        QDBusPendingReply< uint > reply = QDBusConnection::sessionBus().asyncCall(call);
        reply.waitForFinished();

        if (reply.isValid() && reply.value() > 0) {

                QDBusConnection::sessionBus().connect(QLatin1String("org.kde.Solid.PowerManagement"),
                                                      QLatin1String("/org/kde/Solid/PowerManagement/Actions/SuspendSession"),
                                                      QLatin1String("org.kde.Solid.PowerManagement.Actions.SuspendSession"),
                                                      QLatin1String("resumingFromSuspend"),
                                                      this,
                                                      SIGNAL(resumingFromSuspend()));
        }
    }
}
