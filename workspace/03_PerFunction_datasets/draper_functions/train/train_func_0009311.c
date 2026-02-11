connectVisualization(QObject *visualization, uint pollingInterval,
                                         Plasma::IntervalAlignment alignment)
{


    QMap<QObject *, SignalRelay *>::iterator objIt = d->relayObjects.find(visualization);
    bool connected = objIt != d->relayObjects.end();
    if (connected) {


        SignalRelay *relay = objIt.value();
        if (relay) {


            if (relay->m_interval == pollingInterval) {


                return;
            }

            if (relay->receiverCount() == 1) {

                d->relays.remove(relay->m_interval);
                delete relay;
            } else {
                disconnect(relay, SIGNAL(dataUpdated(QString,Plasma::DataEngine::Data)),
                           visualization, SLOT(dataUpdated(QString,Plasma::DataEngine::Data)));

            }
        } else if (pollingInterval < 1) {


            return;
        } else {
            disconnect(this, SIGNAL(dataUpdated(QString,Plasma::DataEngine::Data)),
                       visualization, SLOT(dataUpdated(QString,Plasma::DataEngine::Data)));
        }
    } else {
        connect(visualization, SIGNAL(destroyed(QObject*)),
                this, SLOT(disconnectVisualization(QObject*)));
    }

    if (pollingInterval < 1) {

        d->relayObjects[visualization] = 0;
        connect(this, SIGNAL(dataUpdated(QString,Plasma::DataEngine::Data)),
                visualization, SLOT(dataUpdated(QString,Plasma::DataEngine::Data)));
    } else {


        bool immediateUpdate = connected || d->relayObjects.count() > 1;
        SignalRelay *relay = d->signalRelay(this, visualization, pollingInterval,
                                            alignment, immediateUpdate);
        connect(relay, SIGNAL(dataUpdated(QString,Plasma::DataEngine::Data)),
                visualization, SLOT(dataUpdated(QString,Plasma::DataEngine::Data)));
    }
}
