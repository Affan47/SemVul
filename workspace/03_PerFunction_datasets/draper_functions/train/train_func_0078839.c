sendMessageBoxAnswer(int result)
{
    Q_D(SlaveInterface);
    if (!d->connection) {
        return;
    }

    if (d->connection->suspended()) {
        d->connection->resume();
    }
    QByteArray packedArgs;
    QDataStream stream( &packedArgs, QIODevice::WriteOnly );
    stream << result;
    d->connection->sendnow(CMD_MESSAGEBOXANSWER, packedArgs);
    kDebug(7007) << "message box answer" << result;
}
