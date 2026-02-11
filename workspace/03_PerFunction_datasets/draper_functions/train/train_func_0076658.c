dispatchLoop()
{
    while (!d->exit_loop) {
        if (d->timeout && (d->timeout < time(0))) {
            QByteArray data = d->timeoutData;
            d->timeout = 0;
            d->timeoutData = QByteArray();
            special(data);
        }

        Q_ASSERT(d->appConnection.inited());

        int ms = -1;
        if (d->timeout)
            ms = 1000 * qMax<time_t>(d->timeout - time(0), 1);

        int ret = -1;
        if (d->appConnection.hasTaskAvailable() || d->appConnection.waitForIncomingTask(ms)) {

            int cmd;
            QByteArray data;
            ret = d->appConnection.read(&cmd, data);

            if (ret != -1) {
                if (d->inOpenLoop)
                    dispatchOpenCommand(cmd, data);
                else
                    dispatch(cmd, data);
            }
        } else {
            ret = d->appConnection.isConnected() ? 0 : -1;
        }

        if (ret == -1) {

            if (!d->exit_loop && d->isConnectedToApp && !d->poolSocket.isEmpty()) {
                disconnectSlave();
                d->isConnectedToApp = false;
                closeConnection();
                connectSlave(d->poolSocket);
            } else {
                break;
            }
        }


        if (wasKilled()) {
            kDebug(7019) << "slave was killed, returning";
            break;
        }


        QCoreApplication::sendPostedEvents(NULL, QEvent::DeferredDelete);
    }


    QCoreApplication::sendPostedEvents(NULL, QEvent::DeferredDelete);
}
