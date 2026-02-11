signalRelay(const DataContainer *dc, QObject *visualization,
                                               uint pollingInterval,
                                               Plasma::IntervalAlignment align,
                                               bool immediateUpdate)
{
    QMap<uint, SignalRelay *>::const_iterator relayIt = relays.constFind(pollingInterval);
    SignalRelay *relay = 0;


    if (relayIt == relays.constEnd()) {
        relay = new SignalRelay(const_cast<DataContainer*>(dc), this,
                                pollingInterval, align, immediateUpdate);
        relays[pollingInterval] = relay;
    } else {
        relay = relayIt.value();
    }

    relayObjects[visualization] = relay;
    return relay;
}
