authorizeAction(const QString& action, const QByteArray& callerID)
{
    if (!m_currentAction.isEmpty()) {
        return static_cast<uint>(Action::Error);
    }

    m_currentAction = action;

    uint retVal;

    QTimer *timer = responder->property("__KAuth_Helper_Shutdown_Timer").value<QTimer*>();
    timer->stop();

    if (isCallerAuthorized(action, callerID)) {
        retVal = static_cast<uint>(Action::Authorized);
    } else {
        retVal = static_cast<uint>(Action::Denied);
    }

    timer->start();
    m_currentAction.clear();

    return retVal;
}
