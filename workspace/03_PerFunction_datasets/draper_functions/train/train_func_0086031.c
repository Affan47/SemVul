GetState(const QString &piece, const QDBusMessage &message)
{
    message.setDelayedReply(true);
    QDBusMessage reply = message.createReply();


    QMetaObject::invokeMethod(
                parent(),
                "GetState",
                Qt::QueuedConnection,
                Q_ARG(QString, piece),
                Q_ARG(QDBusMessage, reply)
                );
}
