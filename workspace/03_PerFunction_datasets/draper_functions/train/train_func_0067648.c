disconnectNotify(const char *signal)
{
    QByteArray ba(signal);
    if (d->m_connectedSignals[ba] <= 1) {
        disconnect(d->m_engine, signal, this, signal);
        d->m_connectedSignals.remove(ba);
    } else {
        d->m_connectedSignals[ba]--;
    }
}
