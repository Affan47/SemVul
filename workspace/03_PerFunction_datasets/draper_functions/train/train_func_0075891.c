forceImmediateUpdate()
{
    if (d->dirty) {
        d->dirty = false;
        emit dataUpdated(objectName(), d->data);
    }

    foreach (SignalRelay *relay, d->relays) {
        relay->forceImmediateUpdate();
    }
}
