performAction(const QString &action, const QByteArray &callerID, QByteArray arguments)
{
    if (!responder) {
        return ActionReply::NoResponderReply.serialized();
    }

    if (!m_currentAction.isEmpty()) {
        return ActionReply::HelperBusyReply.serialized();
    }

    QVariantMap args;
    QDataStream s(&arguments, QIODevice::ReadOnly);
    s >> args;

    m_currentAction = action;
    emit remoteSignal(ActionStarted, action, QByteArray());
    QEventLoop e;
    e.processEvents(QEventLoop::AllEvents);

    ActionReply retVal;

    QTimer *timer = responder->property("__KAuth_Helper_Shutdown_Timer").value<QTimer*>();
    timer->stop();

    if (BackendsManager::authBackend()->isCallerAuthorized(action, callerID)) {
        QString slotname = action;
        if (slotname.startsWith(m_name + QLatin1Char('.'))) {
            slotname = slotname.right(slotname.length() - m_name.length() - 1);
        }

        slotname.replace(QLatin1Char('.'), QLatin1Char('_'));

        bool success = QMetaObject::invokeMethod(responder, slotname.toLatin1(), Qt::DirectConnection,
                                                 Q_RETURN_ARG(ActionReply, retVal), Q_ARG(QVariantMap, args));

        if (!success) {
            retVal = ActionReply::NoSuchActionReply;
        }

    } else {
        retVal = ActionReply::AuthorizationDeniedReply;
    }

    timer->start();

    emit remoteSignal(ActionPerformed, action, retVal.serialized());
    e.processEvents(QEventLoop::AllEvents);
    m_currentAction.clear();
    m_stopRequest = false;

    return retVal.serialized();
}
